#include <WiFi.h>
#include <M5Stack.h>

#define count_of_args 1

const char* ssid     = "amperkot";
const char* password = "89252930177";


String message = "";
String headers_info[count_of_args] = {"msg"};
String data_info[count_of_args] = {"None"};


WiFiServer server(80);

void setup()
{
  M5.begin();
  set_data_by_key("msg", readFile(SD, "/message.txt"));
  updateText_show();
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
  showIP();
}

int value = 0;

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("OK");

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.indexOf("HTTP/1.1") != -1) {
          decode_data(currentLine);
          updateText();
          updateText_show();
        }

      }
    }
    client.stop();
  }
  // updateText();
  // updateText_show();
}

String get_data_by_key(String key)
{
  for (uint8_t i = 0; i < count_of_args; i++)
  {
    if  (headers_info[i] == key) return data_info[i];
  }
}

void set_data_by_key(String key, String data)
{

  for (uint8_t i = 0; i < count_of_args; i++)
  {
    if  (headers_info[i] == key) {
      data_info[i] = data;
      return;
    }
  }
}

void updateText()
{
  writeFile(SD, "/message.txt", get_data_by_key("msg").c_str());
}
void updateText_show()
{
  M5.Lcd.setTextColor( WHITE, BLACK);
  M5.Lcd.setTextSize(5);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println(readFile(SD, "/message.txt"));
  showIP();

}

void decode_data(String data)
{
  if (data.indexOf("?") == -1) return;
  String local_string = "";
  for (int i = data.indexOf("HTTP/1.1") - 1; i > 0 ; i--)
  {
    if (data[i] != '?')
    {
      local_string = data[i] + local_string;
    }
    else
    {
      break;
    }
  }
  local_string += "&";
  uint8_t i = 0;
  String ministr = "";
  while ( i < count_of_args)
  {
    for (uint8_t j = 0; j < local_string.length(); j++)
    {
      if (local_string[j] == '&')
      {
        data_info[i] =  ministr;
        i += 1;
        ministr = "";
      }
      else if (local_string[j] == '=')
      {
        headers_info[i] = ministr;
        ministr = "";
      }
      else
      {
        ministr += local_string[j];
      }
    }
    i += 1;
  }

}

String readFile(fs::FS &fs, const char * path) {
  String data = "";
  File file = fs.open(path);
  if (!file) {
    return "No message";
  }
  while (file.available()) {
    char ch = file.read();
    data += ch;
  }

  if (data != "")
  {
    return data;
  }
  else {
    return "No message";
  }
}

void writeFile(fs::FS &fs, const char * path, String message) {
  File file = fs.open(path, FILE_WRITE);
  file.print(message);
}

void showIP()
{
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor( WHITE, BLUE);
  M5.Lcd.setCursor(20, 200);
  M5.Lcd.print(WiFi.localIP());
}
