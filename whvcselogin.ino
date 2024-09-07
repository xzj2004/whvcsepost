#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// 替换为你的Wi-Fi SSID和密码
const char* ssid = "ssid";
const char* password = "password";

// 替换为你的校园网登录用户名和密码
const char* campusUsername = "youradmin";
const char* campusPasswordHash = "yourpasswordcookie";

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  loginToCampusNetwork();
}

void loop() {
  // 在这里添加循环执行的任务
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
}

void loginToCampusNetwork() {
  HTTPClient http;
  WiFiClient client;
  String url = "http://10.80.1.122/eportal/InterFace.do?method=login";

  // 使用WiFiClient实例初始化HTTPClient
  http.begin(client, url);

  // 将常量字符数组转换为String类型
  String username = campusUsername;
  String passwordHash = campusPasswordHash;

  // 构造请求体
  String body = "userId=" + username + "&password=" + passwordHash + "&service=after-auth" + "&queryString=wlanuserip%253D10.34.108.89%2526wlanacname%253D%2526nasip%253D172.10.1.1%2526wlanparameter%253D96-7a-3c-66-3f-15%2526url%253Dhttp%253A%252F%252F123.123.123.123%252F%2526userlocation%253Dethtrunk%252F200%253A1708.0" + "&operatorPwd=" + "&operatorUserId=" + "&validcode=" + "&passwordEncrypt=true";

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(body);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  WiFiClient webtestClient;
  HTTPClient webtest;
  webtest.begin(webtestClient, "http://baidu.com");
  int code = webtest.GET();
  if (code == 200) {
    Serial.println("Sucessful Internet access");
  }
  http.end();
}