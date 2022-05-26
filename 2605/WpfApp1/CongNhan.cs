using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    class CongNhan
    {
        public string hoTen { get; set; }
        public string gioiTinh { get; set; }
        public int soNgayCong { get; set; }
        public int luong { get; set; }
        public int thuong 
        {
            get
            {
                if (luong >= 27) return ((int)(luong * 0.1));
                else return 0;
            }
            
        }

        public CongNhan()
        {

        }

        public CongNhan(string hoTen, string gioiTinh, int soNgayCong, int luong)
        {
            this.hoTen = hoTen;
            this.gioiTinh = gioiTinh;
            this.soNgayCong = soNgayCong;
            this.luong = luong;
          
        }
       
        public override string ToString()
        {
            return hoTen + " - " + gioiTinh + " - " + soNgayCong + " - " + luong + " - " + thuong;
        }
    }
}
