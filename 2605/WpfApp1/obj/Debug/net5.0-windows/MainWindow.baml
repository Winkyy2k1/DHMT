   M S B A M L   `   `   `  ����B  >WpfApp1, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:WpfApp1WpfApp1  5   	       WpfApp1.MainWindow   5   	   W SPresentationCore, Version=5.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=5.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=5.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=5.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=5.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   'localclr-namespace:WpfApp1     5   	     � Title$  BuiThiHai_2019606166��5   	   $	��450��6&   $	��800��63   .��5	      � .+�5
   
   �� $$��CHƯƠNG TRÌNH TÍNH LƯƠNG ��6   $��Center=�63   $��0,27,0,0q�6P   $	��Top=�6b   $��20(�6z   �� 5   
   $��	Họ tên��6   $
��Left=�6!   $��	68,90,0,0q�6<   $	��Top=�6O   �� 5   
   $��Giới tính��6   $
��Left=�6$   $��
68,121,0,0q�6?   $	��Top=�6S   �� 5   
   $��Số ngày công��6   $
��Left=�6'   $��
68,152,0,0q�6B   $	��Top=�6V   �� 5   
   $��Lương��6   $
��Left=�6    $��
68,183,0,0q�6;   $	��Top=�6O   �� 5   
   -   5        $��txtTen��5      $
��Left=�6    $��
202,96,0,0q�6;   $�� ��6O    �� TextWrapping$
 Wrap=�6X   $	��Top=�6l   $	��220��6�    J� RenderTransformOrigin$ 0.5,0.5&�6�   .��6�   5      	� 5   
   -   5        $��radioNam��5   $   $	��Nam��6    	� 	GroupName$ GioiTinh��64   $
��Left=�6I   $��202,126,0,0q�6d   $	��Top=�6y   	� 5   
   -   5        $��radioNu��5   #   $��Nu��6   $ GioiTinh��63    d� 	IsChecked$
 TrueY�6H   $
��Left=�6Y   $��343,126,0,0q�6t   $	��Top=�6�   �� 5   
   -   5        $��txtSoNgayCong��5      $
��Left=�6'   $��206,156,0,0q�6B   $�� ��6W   $
 Wrap=�6_   $	��Top=�6s   $	��220��6�   �� 5   
   -   5        $��txtLuong��5      $
��Left=�6"   $��206,187,0,0q�6=   $�� ��6R   $
 Wrap=�6Z   $	��Top=�6n   $	��220��6�   �� 5   
   -   5        $��listText��5      $	��100��6"   $��68,233,182,101q�6/   �� 5   
   -   5        $��btnXoa��5   $   $��Nhập lại��6   $
��Left=�62   $��100,381,0,0q�6M   $	��Top=�6b   6z   �� 5   
   -   5        $��
btnChiTiet��5   $   $��
Chi Tiết��6   $
��Left=�66   $��230,381,0,0q�6Q   $	��Top=�6f   6~   �� 5   
   -	   5        $��btnThem��5       $��Thêm��6   $
��Left=�6/   $��360,381,0,0q�6J   $	��Top=�6_   6w   �� 5   
   -
   5        $��btnDong��5       $��Đóng��6   $
��Left=�60   $��600,381,0,0q�6K   $	��Top=�6`   6x   �� 5   
   -   5        $��	btnXoa1Ng��5   '   $��Xoá 1 người��6   $
��Left=�68   $��471,381,0,0q�6S   $	��Top=�6h   $ 0.215,-0.274&�6�   6�   5%      5&      