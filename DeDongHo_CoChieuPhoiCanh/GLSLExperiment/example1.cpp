//Chương trình vẽ 1 hình lập phương đơn vị theo mô hình lập trình OpenGL hiện đại

#include "Angel.h"  /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/


// remember to prototype
void generateGeometry( void );
void initGPUBuffers( void );
void shaderSetup( void );
void display( void );
void keyboard( unsigned char key, int x, int y );


typedef vec4 point4;
typedef vec4 color4;
using namespace std;

// Số các đỉnh của các tam giác
const int NumPoints = 36;

point4 points[NumPoints]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
vec3 normals[NumPoints]; /*Danh sách các vector pháp tuyến ứng với mỗi đỉnh*/


point4 vertices[8]; /* Danh sách 8 đỉnh của hình lập phương*/
color4 vertex_colors[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/

GLuint program;

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;
GLfloat Theta[NumAxes] = { 0.0, 0.0, 0.0 };
mat4 ctm;
GLuint loc_modelMatrix;
point4 new_points[NumPoints];


//Khai báo biến chứa khung nhìn
mat4 projection;
GLuint projection_loc;
mat4 view;
GLuint view_loc;
mat4 model;
float drv = 5.0;//Độ để quay bằng view



/* Khởi tạo các tham số chiếu sáng - tô bóng*/
point4 light_position(1.0, 0.0, 2.0, 0.0);
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);

color4 material_ambient(1.0, 0.0, 1.0, 1.0);
color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
color4 material_specular(1.0, 0.8, 0.0, 1.0);
float material_shininess = 100.0;

color4 ambient_product = light_ambient * material_ambient; //nguồn sáng môi trường
color4 diffuse_product = light_diffuse * material_diffuse; // ánh sáng khuếch tán
color4 specular_product = light_specular * material_specular; // ánh sáng phản chiếu/chói


void initCube()
{
	// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
	vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
	vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
	vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
	vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
	vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
	vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
	vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
	vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

	// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
	vertex_colors[0] = color4(0.0, 0.0, 0.0, 1.0); // black
	vertex_colors[1] = color4(1.0, 0.0, 0.0, 1.0); // red
	vertex_colors[2] = color4(1.0, 1.0, 0.0, 1.0); // yellow
	vertex_colors[3] = color4(0.0, 1.0, 0.0, 1.0); // green
	vertex_colors[4] = color4(0.0, 0.0, 1.0, 1.0); // blue
	vertex_colors[5] = color4(1.0, 0.0, 1.0, 1.0); // magenta
	vertex_colors[6] = color4(1.0, 0.8, 0.0, 1.0); // orange
	vertex_colors[7] = color4(0.0, 1.0, 1.0, 1.0); // cyan
}
int Index = 0;
void quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
{
	vec4 u = vertices[b] - vertices[a];
	vec4 v = vertices[c] - vertices[b];
	vec3 normal = normalize(cross(u, v));

	normals[Index] = normal;  colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[b]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[d]; Index++;
}
void makeColorCube(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/

{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}
void generateGeometry( void )
{
	initCube();
	makeColorCube();
}


void initGPUBuffers( void )
{
	// Tạo một VAO - vertex array object
	GLuint vao;
    glGenVertexArrays( 1, &vao );     
    glBindVertexArray( vao );

   // Tạo và khởi tạo một buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normals), normals);
	
}



void shaderSetup( void )
{
	// Nạp các shader và sử dụng chương trình shader
    program = InitShader( "vshader1.glsl", "fshader1.glsl" );   // hàm InitShader khai báo trong Angel.h
    glUseProgram( program );

    // Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
    GLuint loc_vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( loc_vPosition );
    glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc_vColor);
	glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));


	GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(colors)));


	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);  // Nguồn sáng môi trường
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);  // ánh sáng khuếch tán
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product); // ánh sáng phản chiếu/chói
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position); // ánh sáng điểm
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);  // độ sắc nét



	loc_modelMatrix = glGetUniformLocation(program, "modelMatrix");
	//Thêm vào hàm shaderSetup
	projection_loc = glGetUniformLocation(program, "Projection");
	view_loc = glGetUniformLocation(program, "View");
	
	glEnable(GL_DEPTH_TEST);
    glClearColor( 1.0, 1.0, 1.0, 1.0 );        /* Thiết lập màu trắng là màu xóa màn hình*/
}


#pragma region Dong Ho
mat4 instance;
mat4 instance_base;
float ngang = 2, dai = 2;
GLfloat theta[] = { 0.0, 0.0, 0.0 };
float dich = 0;
void Mat() {
	instance = Scale(ngang, dai, 0.2);
	material_diffuse = color4(1.0, 0.0, 0.0, 1.0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(loc_modelMatrix, 1, GL_TRUE, instance_base*instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Kim() {
	instance = Translate(0.25,0,0.2)* Scale(0.5, 0.1, 0.2);
	material_diffuse = color4(0.0, 0.0, 1.0, 1.0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(loc_modelMatrix, 1, GL_TRUE, instance_base * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Gio12() {
	instance = Translate(0, 0.8, 0.2)*RotateZ(90)* Scale(0.2, 0.1, 0.2);
	material_diffuse = color4(0.0, 0.0, 1.0, 1.0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(loc_modelMatrix, 1, GL_TRUE, instance_base * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Gio3() {
	instance = Translate(0.8, 0, 0.2)* Scale(0.2, 0.1, 0.2);
	material_diffuse = color4(0.0, 0.0, 1.0, 1.0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(loc_modelMatrix, 1, GL_TRUE, instance_base * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void Gio6() {
	instance = Translate(0, -0.8, 0.2) * RotateZ(90) * Scale(0.2, 0.1, 0.2);
	material_diffuse = color4(0.0, 0.0, 1.0, 1.0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(loc_modelMatrix, 1, GL_TRUE, instance_base * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void Gio9() {
	instance = Translate(-0.8, 0, 0.2) * Scale(0.2, 0.1, 0.2);
	material_diffuse = color4(0.0, 0.0, 1.0, 1.0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(loc_modelMatrix, 1, GL_TRUE, instance_base * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void DongHo() {
	instance_base =Translate(dich,0,0)* RotateY(theta[0])*RotateZ(180);
	Mat();
	instance_base = Translate(dich, 0, 0) * RotateY(theta[0]) * RotateZ(180)*RotateZ(theta[1]+90);
	Kim();
	instance_base = Translate(dich, 0, 0) * RotateY(theta[0]) * RotateZ(180);
	Gio12();
	Gio3();
	Gio6();
	Gio9();
}
#pragma endregion



//Hàm Tạo khung nhìn
void reshape(int width, int height)
{

	vec4 eye(-1, 1,3, 1); //nhìn phải nhìn từ dưới lên
	vec4 at(0, 0, 1, 1); // vị trí đặt vật
	vec4 up(0, 1, 0, 1); //tọa độ chỉ ra up-vector của camera.
	view = LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);
	projection = Frustum(1,-1, 1, -1, 1, 10); //left right top button znear zfar
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
	glViewport(0, 0, width, height);
}





void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );   
	const vec3 viewer_pos(0, 0, 3.0);  /*Trùng với eye của camera*/
	DongHo();
	glutSwapBuffers();									   
}


void keyboard( unsigned char key, int x, int y )
{
	// keyboard handler

    switch ( key ) {
    case 033:			// 033 is Escape key octal value
        exit(1);		// quit program
        break;
	
	case 's':			// quay 30 độ
		theta[1] += -30;		// quit program
		glutPostRedisplay();
		break;
	case 't':			// dịch trái
		dich += ngang/10;		// quit program
		glutPostRedisplay();
		break;
	case 'p':			//dịch phải
		dich += -dai/10;		// quit program
		glutPostRedisplay();
		break;
    }
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON: Axis = Xaxis; break;
		case GLUT_MIDDLE_BUTTON: Axis = Yaxis; break;
		case GLUT_RIGHT_BUTTON: Axis = Zaxis; break;
		}
	}
}

void spinCube(void)
{

	
	glutPostRedisplay();

	
}

int main( int argc, char **argv )
{
	// main function: program starts here

    glutInit( &argc, argv );                       
    glutInitDisplayMode( GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize( 640, 640 );                 
	glutInitWindowPosition(100,150);               
    glutCreateWindow( "Drawing a Cube" );            
	
	   
	glewInit();										

	
	generateGeometry();
	initGPUBuffers();
    shaderSetup( );                               

      
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
    return 0;
}
