using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaiDung
{
    class NhanVien
    {
        public String hoTen { get; set; }
        public String loaiNV { get; set; }
        public String ngaySinh { get; set; }
        public double  tien { get; set; }
        public double hoaHong()
        {
            double hoaHong = 0;
            if (tien < 1000) hoaHong = 0;
            else
            {
                if (tien >= 1000 && tien <= 5000)
                {
                    hoaHong = tien * 0.05;
                }
                else hoaHong = tien * 0.1;
            }
            return hoaHong;
        }

        public NhanVien()
        {

        }
        public NhanVien(string hoTen, string loaiNV, string ngaySinh, double tien)
        {
            this.hoTen = hoTen;
            this.loaiNV = loaiNV;
            this.ngaySinh = ngaySinh;
            this.tien = tien;
        }

        public override string ToString()
        {
            return hoTen + " - " + ngaySinh + " - " + loaiNV + " - Tiền bán hàng: " + tien + " - Hoa hồng: " + hoaHong();
        }
    }
}
