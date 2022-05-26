using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ObservableCollection<CongNhan> liCongNhan = new ObservableCollection<CongNhan>();
        public MainWindow()
        {
            InitializeComponent();
            WindowStartupLocation = WindowStartupLocation.CenterScreen;
         
            //List<CongNhan> liCongNhan = new List<CongNhan>();
        }

        private void btnDong_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void btnXoa_Click(object sender, RoutedEventArgs e)
        {
            txtTen.Clear();
            txtLuong.Clear();
            txtSoNgayCong.Clear();
            radioNam.IsChecked = true;
            txtTen.Focus();

        }

        private void btnThem_Click(object sender, RoutedEventArgs e)
        {
          
            string Ten, GioiTinh, SoNgayCong, Luong, Thuong;
            string Loi = "";

            Ten = txtTen.Text;
            if(radioNam.IsChecked== true)
            {
                GioiTinh = "Nam";
            } else { GioiTinh = "Nữ"; }

            SoNgayCong = txtSoNgayCong.Text;
            Luong = txtLuong.Text;
              
            if(string.IsNullOrWhiteSpace(txtTen.Text))
            {
                Loi += " Bạn phải nhập họ tên. ";
            }
            if (!Regex.IsMatch(txtSoNgayCong.Text, @"\d+"))
            {
                Loi += "\n Ban phai nhap vao so ngay cong là so ";
            }
                else
                {
                    int so = int.Parse(txtSoNgayCong.Text);
                    if (so < 20 || so >30 )
                    {
                        Loi += "\n Ban phai nhap so ngay cong tu 20 den 30 ";
                    }
                }
            if (!Regex.IsMatch(txtLuong.Text, @"\d+"))
            {
                Loi += "\n Ban phai nhap vao luong là so ";
            }
            else
            {
                int so = int.Parse(txtLuong.Text);
                if (so < 3000 || so > 5000)
                {
                    Loi += "\n Ban phai nhap luong khoang 3000 - 5000";
                }
            }
          
            if( Loi != "")
            {
                MessageBox.Show(Loi);
            }
            else
            {
                MessageBox.Show("Dữ liệu hợp lệ. Thêm thành công! ");
                CongNhan cn = new CongNhan();
                cn.hoTen = Ten;
                cn.gioiTinh = GioiTinh;
                cn.soNgayCong = int.Parse(SoNgayCong);
                cn.luong = int.Parse(Luong);
                
                liCongNhan.Add(cn);
                //listText.Items.Add(liCongNhan);
                listText.ItemsSource = liCongNhan;
               
            }


        }

        private void btnChiTiet_Click(object sender, RoutedEventArgs e)
        {
            CongNhan cn = listText.SelectedItem as CongNhan;
            if (cn == null)
            MessageBox.Show("Bạn chưa chọn người nào trong danh sách. ");
            else
            {
                Window2 wd2 = new Window2();
                wd2.txtTen.Text = cn.hoTen;
                if (cn.gioiTinh == "Nam")
                {
                    wd2.radioNam.IsChecked = true;
                }
                else wd2.radioNu.IsChecked = true;

                wd2.txtSoNgayCong.Text = cn.soNgayCong.ToString();
                wd2.txtLuong.Text = cn.luong.ToString();
                wd2.txtThuong.Text = cn.thuong.ToString();

                wd2.Show(); // mở cửa sổ 2
                Close(); // đóng cửa sổ 1 
            }           
            
        }

        private void btnXoa1Ng_Click(object sender, RoutedEventArgs e)
        {
            try
            {

                CongNhan cn = listText.SelectedItem as CongNhan;
                if (cn == null)
                    MessageBox.Show("Bạn chưa chọn người nào trong danh sách. ");
                else
                {   
                    MessageBoxResult msg = MessageBox.Show("Bạn có chắc xóa không?", "Thông báo", MessageBoxButton.YesNo, MessageBoxImage.Question);
                    if (msg == MessageBoxResult.Yes)
                    {
                        liCongNhan.Remove(cn);
                    }
                   
                }
            }
            catch( Exception e1)
            {
                MessageBox.Show(" Có lỗi xảy ra: " + e1.Message);
            }
        }  
    }
}
