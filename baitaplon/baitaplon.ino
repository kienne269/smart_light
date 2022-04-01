#include <SPI.h>
#include <Ethernet2.h>

int PIR = 8;
int LIGHT = A0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
   
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
 
  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  //giọng nói---------------

  Serial.begin(9600);
  // put your setup code here, to run once:


  //phím bấm---------------------------
}

void loop() {

  String readString;
  EthernetClient client = server.available();

//---------Nút bấm trên điện thoại--------------------
  if(Serial.available()>0){
    readString="";
    String c = Serial.readString();  //Tiến hành đọc serial
    readString += c;   //tạo chuỗi dữ liệu "bật" , "tắt"
  }

  if (readString.length() > 0) {
    Serial.println(readString);
  }
  if(readString=="bật đèn 1")
  {
    digitalWrite(2, LOW);
    Serial.println('đèn bật');
    delay(500);
  }else if(readString=="bật đèn 2"){
    digitalWrite(3, LOW);
    Serial.println('đèn bật');
    delay(500);
  }else if(readString=="Tắt Đèn 1"){
    digitalWrite(2, HIGH);
    Serial.println('đèn tắt');
    delay(500);
  } else if(readString=="Tắt Đèn 2"||readString=="tắt đèn 2"){
    digitalWrite(3, HIGH);
    Serial.println('đèn tắt');
    delay(500);}
    else if(readString=="bật hai đèn"){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    Serial.println('đèn tắt');
    delay(500);
  } else if(readString=="tắt 2 đèn"){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    Serial.println('đèn tắt');
    delay(500);
  } else if(readString=="tự động"){
    int giatri_analog = analogRead(A0);
    int value = digitalRead(PIR);
    int L = digitalRead(LIGHT);
    if(L==1) {
      if (value == HIGH) {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
         Serial.println('đèn bật');
         delay(5000);
      } 
      else {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
         Serial.println('đèn tắt');
    delay(500);
      }
    } else {
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      Serial.println('đèn tắt');
    delay(500);
    }
    delay(500);
  }
//---------Nút bấm trên máy tính--------------------
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if(readString.length() < 100) {
          // lưu trữ các ký tự thành chuỗi
          readString += c;
        }
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header

          if (readString.indexOf("1on") > 0) {
            digitalWrite(2, LOW);
            Serial.println("đèn 1 bật");
          }
          if (readString.indexOf("1off") > 0) {
            digitalWrite(2, HIGH);
            Serial.println("đèn 1 tắt");
          }
          if (readString.indexOf("2on") > 0) {
            digitalWrite(3, LOW);
            Serial.println("đèn 2 bật");
          }
          if (readString.indexOf("2off") > 0) {
            digitalWrite(3, HIGH);
            Serial.println("đèn 2 tắt");
          }
          if (readString.indexOf("tathet") > 0) {
            digitalWrite(2, HIGH);
            digitalWrite(3, HIGH);
            Serial.println("cả 2 đèn tắt");
          }
          if (readString.indexOf("bathet") > 0) {
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            Serial.println("cả 2 đèn bật");
          }
//=================================================================
          int TB1 = digitalRead(2);   // Biến TB1 cập nhật trạng thái
          int TB2 = digitalRead(3);
//============================================
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
//          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println(F("<head>"));
          client.println(F("<meta charset='UTF-8'>"));
          client.println(F("<meta http-equiv='X-UA-Compatible' content='IE=edge'>"));
          client.println(F("<meta name='viewport' content='width=device-width, initial-scale=1.0'>"));
          client.println(F("<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css' integrity='sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u' crossorigin='anonymous'>"));
          client.println(F("<link rel='stylesheet' href='https://vinfastauto.ml/style.css'>"));
          client.println(F("<link rel='preconnect' href='https://fonts.googleapis.com'>"));
          client.println(F("<link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>"));
          client.println(F("<link href='https://fonts.googleapis.com/css2?family=Montserrat:wght@500;900&family=Rowdies:wght@300;400;700&display=swap' rel='stylesheet'>"));
          client.println(F("<title>Bài tập lớn</title>"));
          client.println(F("</head>"));
          client.println(F("<body>"));
          client.println(F("<div class='app'>"));
          client.println(F("<div class='header'>"));
          client.println(F("<img src='https://user-images.githubusercontent.com/88047306/158065587-7e0eec59-435f-4e94-b6ed-f1fab000f1e9.jpg' alt='logo'>"));
          client.println(F("<h1 class='header__title'>Môn thiết kế hệ thống nhúng</h1>"));
          client.println(F("</div>"));
          client.println(F("<div class='body'>"));
          client.println(F("<h3 class='text-center'> Giao diện điều khiển thiết bị</h3>"));
          client.println(F("<div class='body__main'>"));
          client.println(F("<div class='row'>"));
          client.println(F("<div class='col-md-12'>"));
          client.println(F("<table class='table text-center'>"));
          client.println(F("<thead><tr>"));
          client.println(F("<th class='text-center'>Tên thiết bị</th>"));
          client.println(F("<th class='text-center'>Chọn chế độ</th>"));
          client.println(F("</tr></thead>"));
          client.println(F("<tbody>"));
          client.println(F("<tr>"));
          client.println(F("<td style='line-height: 46px;'>Thiết bị 1 - Đang"));
          if (TB1 == LOW) {
              client.println(F("<span>bật</span></td>"));
              client.println(F("<td><a class='btn btn-danger btn-lg' href='1off'>Tắt</buttLigado>"));
          } else if(TB1 == HIGH) {
              client.println(F("<span>tắt</span></td>"));
              client.println(F("<td><a class='btn btn-success btn-lg' href='1on'>Bật</buttLigado>"));
          }
          client.println(F("</td></tr>"));
          client.println(F("<tr>"));
          client.println(F("<td style='line-height: 46px;'>Thiết bị 2 - Đang"));
          if (TB2 == LOW) {
              client.println(F("<span>bật</span></td>"));
              client.println(F("<td><a class='btn btn-danger btn-lg' href='2off'>Tắt</a></td></tr>"));
          } else if(TB2 == HIGH){
              client.println(F("<span>tắt</span></td>"));
              client.println(F("<td><a class='btn btn-success btn-lg' href='2on'>Bật</a></td></tr>"));
          }
          client.println(F("</tr>"));
          client.println(F("<tr>"));
          client.println(F("<td style='line-height: 46px;'>Tất cả thiết bị </td>"));
          client.println(F("<td>"));
          client.println(F("<a class='btn btn-danger btn-lg' href='tathet' > ALL OFF</a>"));
          client.println(F("<a class='btn btn-success btn-lg' href='bathet' > ALL ON</a>"));
          client.println(F("</td></tr>"));
          client.println(F("</tbody>"));
          client.println(F("</table>"));
          client.println(F("</div></div>"));
          client.println(F("<a class='btn btn-success btn-lg' href='/'>Refresh</a>"));
          client.println(F("</div></div></div>"));
          client.println(F("</body>"));
          client.println(F("</html>"));

          client.stop();
          readString="";  //  Reset lại chuỗi cho lần đọc tiếp theo
        
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
 }


}
