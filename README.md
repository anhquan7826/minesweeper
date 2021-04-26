# minesweeper
## Giới thiệu.
Dò mìn hay gỡ boom (tiếng Anh: Minesweeper) là một trò chơi trên máy tính dành cho một người chơi.
Trong Dò mìn, người chơi phải mở được tất cả các ô không có mìn trên một bảng ô vuông.
## Cách chơi
* Người chơi khởi đầu với một bảng ô vuông trống thể hiện "bãi mìn".
* Click chuột vào một ô vuông trong bảng. Nếu không may trúng phải ô có mìn (điều này thường xảy ra với người mới chơi) thì trò chơi kết thúc. Trường hợp khác là ô đó không có mìn   và một vùng các ô sẽ được mở ra cùng với những con số. Số trên một ô là lượng mìn trong 8 ô nằm quanh với ô đó.
* Nếu chắc chắn một ô có mìn, người chơi đánh dấu vào ô đó bằng hình lá cờ (click chuột phải).
* Khi 8 ô lân cận trong một số đã có đủ số mìn mà vẫn còn các ô khác thì những ô đó không có mìn
* Trò chơi kết thúc với phần thắng dành cho người chơi nếu mở được tất cả các ô không có mìn.
## Độ khó
* Dễ (beginner): bảng ô vuông 9 × 9 trên đó rải 10 quả mìn
* Trung bình (intermediate): bảng ô vuông 16 × 16 trên đó rải 40 quả mìn
* Khó (expert): bảng ô vuông 30 × 16 trên đó rải 99 quả mìn
## Dependencies
* Linux: các dependencies cần thiết để chạy game:
  ``` sudo apt install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-ttf-2.0-0 ```
* Windows: Tất cả các file DLL cần thiết để game chạy đã ở trong thư mục game. chỉ cần chạy file .exe
