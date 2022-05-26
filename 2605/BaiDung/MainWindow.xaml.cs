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

namespace BaiDung
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ObservableCollection<NhanVien> linv = new ObservableCollection<NhanVien>();
        public MainWindow()
        {
            InitializeComponent();
            WindowStartupLocation = WindowStartupLocation.CenterScreen;
        }

        private void btnNhap_Click(object sender, RoutedEventArgs e)
        {
            try {
                // Kiểm tra điều kiện thêm hợp lệ 
                String sTen, sLoai = "", sNgaySinh, sTien, sHoaHong;
                String Loi = "";

                sTen = txtHoten.Text;
                if (string.IsNullOrEmpty(sTen))
                {
                    Loi += "\n Bạn cần nhập họ và tên. ";
                }
                sNgaySinh = datNgaySinh.Text;
                if (string.IsNullOrEmpty(sNgaySinh))
                {
                    Loi += "\n Bạn cần chọn ngày sinh ";
                }
                else
                {
                    int nam = int.Parse(sNgaySinh.Substring(sNgaySinh.Length - 4, 4));
                    int tuoi = 2022 - nam;
                    if (tuoi < 19 || tuoi > 60)
                    {
                        Loi += "\n Bạn phải chon tuổi từ 19 đến 60.";
                    }
                }
                if (ComChon.SelectedIndex >= 0)
                {
                    sLoai = ComChon.Text;
                }

                sTien = txtTien.Text;
                if (string.IsNullOrEmpty(sTien))
                {
                    Loi += " Ban phải nhập dữ liệu cho tiền thưởng. ";
                }
                else
                {
                    double so = Convert.ToDouble(txtTien.Text);
                    if (so < 0)
                    {
                        Loi += "\n Ban phai nhap so tien > 0  ";
                    }
                }

                if (Loi != "")
                {
                    MessageBox.Show(Loi);

                }
                else
                {
                    MessageBox.Show("Dữ liệu hợp lệ. Thêm vào list thành công. ");

                    NhanVien nv = new NhanVien();
                    nv.hoTen = sTen;
                    nv.loaiNV = sLoai;
                    nv.ngaySinh = sNgaySinh;
                    nv.tien = double.Parse(sTien);
                    linv.Add(nv);
                    listHien.ItemsSource = linv;
                }
            }
            catch( Exception e1)
            {
                MessageBox.Show("Có lỗi xảy ra" + e1);
            }
        }

        private void btnXoa_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                NhanVien nv = listHien.SelectedItem as NhanVien;
                if (nv == null)
                {
                    MessageBox.Show("Bạn chưa chọn nhân viên để hiện. ");
                }
                else
                {
                    MessageBoxResult msg = MessageBox.Show("Bạn có chắc xóa không?", "Thông báo", MessageBoxButton.YesNo, MessageBoxImage.Question);
                    if (msg == MessageBoxResult.Yes)
                    {
                        linv.Remove(nv);
                    }
                    txtHoten.Clear();
                    txtTien.Clear();
                    ComChon.SelectedIndex = -1;
                    datNgaySinh.SelectedDate = DateTime.Now;
                    txtHoten.Focus();
                }
            }
            catch (Exception e1)
            {
                MessageBox.Show(" Có lỗi xảy ra: " + e1);
            }
        }

        private void btnWin2_Click(object sender, RoutedEventArgs e)
        {
             try
            {
                NhanVien nv = listHien.SelectedItem as NhanVien;
                if (nv == null)
                {
                    MessageBox.Show("Bạn chưa chọn nhân viên để hiện. ");
                }
                else
                {
                    Window2 wd2 = new Window2();
                    wd2.txtHoten.Text = nv.hoTen;
                    wd2.txtNgaySinh.Text = nv.ngaySinh;
                    wd2.txtTien.Text = nv.tien.ToString();
                    wd2.comChon.Text = nv.loaiNV;

                    wd2.Show(); // Mở window 2 lên
                    Close(); // Đóng window 1
                }

            } catch (Exception e1)
            {
                MessageBox.Show(" Có lỗi xảy ra" + e1);
            }
        }


    }
}
