sử dụng commandline: ./Bin/BT_Buoi2 ./text.txt <Chuoi ky tu muon them vao file>  
Cờ O_APPEND khiến cho việc ghi dữ liệu sẽ luôn diễn ra ở cuối file, bất kể con trỏ đọc/ghi hiện tại đang ở đâu trong file. Khi gọi hàm write sau khi đã mở file với cờ O_APPEND, dữ liệu sẽ luôn được ghi vào cuối file mà không cần thiết lập lại con trỏ đọc/ghi đến đầu file.
