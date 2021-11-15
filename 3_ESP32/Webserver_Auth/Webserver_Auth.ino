#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "env.h";

String validCookie = COOKIE_BASE + "=" + COOKIE;
String invalidCookie = COOKIE_BASE + "=0";

WebServer server(80);
IPAddress local_IP(192, 168, 1, IP);
IPAddress gateway(192, 168, 1, 255);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

void logout() {
  server.sendHeader("Location", "/");
  server.sendHeader("Cache-Control", "no-cache");
  server.sendHeader("Set-Cookie", invalidCookie);
  server.send(301);
  Serial.println("Logout");
}

bool isAuthorized() {
  if (server.hasHeader("Cookie")) {
    String cookie = server.header("Cookie");
    if (cookie.indexOf(validCookie) != -1) return true;
  }

  return false;
}

String buildMenu() {
  String menu = "<p>Menu:</p>";

  menu += "<ul>";
  if (isAuthorized()) {
    menu += "<li><a href='/profile'>Profile</a></li>";
    menu += "<li><a href='/public'>Public</a></li>";
    menu += "<li><a href='/logout'>Logout</a></li>";
  } else {
    menu += "<li><a href='/'>Login</a></li>";
    menu += "<li><a href='/public'>Public</a></li>";
  }
  menu += "</ul>";

  return menu;
}

void loginPage() {
  String msg;

  if (isAuthorized()) {
    server.sendHeader("Location", "/profile");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", validCookie);
    server.send(301);
  }

  if (server.hasArg("USERNAME_FORM") && server.hasArg("PASSWORD_FORM")) {
    if (server.arg("USERNAME_FORM") == USERNAME && server.arg("PASSWORD_FORM") == PASSWORD) {
      server.sendHeader("Location", "/profile");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", validCookie);
      server.send(301);
      Serial.println("Log in Successful");
      return;
    }

    msg = "Wrong credentials";
    Serial.println("Log in Failed");
  }

  String content = "<html>";
  content += "<head><style>";
  content += "* {box-sizing: border-box; margin: 0; padding: 0;}";
  content += "body {display: flex; flex-direction: column; align-items: center; padding-top: 30px;}";
  content += "input {width: 100%; height: 30px; font-size: 15px; padding: 0 10px;}";
  content += "button {padding: 3px 15px; cursor: pointer;}";
  content += "form {width: 300px; border: 1px solid rgba(0, 0, 0, 0.3); display: flex; flex-direction: column; align-items: center; padding: 10px; border-radius: 5px; margin: 10px;}";
  content += "form div:not(:first-child) {margin-top: 5px;}";
  content += ".cta,.input {width: 100%;}";
  content += ".cta button {width: 100%;}";
  content += "h1 {text-transform: uppercase;}";
  content += "ul {list-style-type: none; display: flex; padding: 10px;}";
  content += "li:not(:last-child) {margin-right: 5px;}";
  content += "a {text-decoration: none; text-transform: capitalize; padding: 5px 15px; background-color: hsl(197, 100%, 53%); border-radius: 5px; color: white;}";
  content += "a:hover {background-color: hsl(197, 100%, 40%);}";
  content += "p.error {color: red; padding-top: 5px; text-transform: capitalize;}";
  content += ".container { width: 100%; min-height: 200px; padding: 20px; display: flex; align-items: center; flex-direction: column; margin-bottom: 5px; }";
  content += "</style></head>";
  content += "<body>";
  content += "<h1>Login</h1>";
  content += "<div class='container'>";
  content += "<form>";
  content += "<div class='input'><input required='true' type='text' name='USERNAME_FORM' placeholder='Username'></div>";
  content += "<div class='input'><input required='true' type='password' name='PASSWORD_FORM' placeholder='Password'></div>";
  content += "<div class='cta'><button type='submit'>Submit</button></div>";
  content += "<p class='error'>" + msg + "</p>";
  content += "</form>";
  content += "</div>";
  content += buildMenu();
  content += "</body>";
  content += "</html>";
  server.send(200, "text/html", content);
}

void profilePage() {
  if (!isAuthorized()) logout();

  String content = "<html>";
  content += "<head><style>";
  content += "* { box-sizing: border-box; margin: 0; padding: 0; }";
  content += "body { display: flex; flex-direction: column; align-items: center; padding-top: 30px; }";
  content += "h1 { text-transform: uppercase; }";
  content += "h2 { text-transform: capitalize; font-weight: 400; margin: 10px 0; }";
  content += "ul { list-style-type: none; display: flex; padding: 10px; }";
  content += "li:not(:last-child) { margin-right: 5px; }";
  content += "a { text-decoration: none; text-transform: capitalize; padding: 5px 15px; background-color: hsl(197, 100%, 53%); border-radius: 5px; color: white; }";
  content += "a:hover { background-color: hsl(197, 100%, 40%); }";
  content += "p { margin: 5px 0; }";
  content += ".item > div { border-bottom: 1.5px dashed red; }";
  content += ".controller { min-width: 300px; display: flex; flex-direction: column; padding: 10px; border-radius: 5px; border: 1px solid rgba(0,0,0,0.3);  }";
  content += ".controller p { text-decoration: dots; }";
  content += ".controller ul { display: flex; flex-direction: column; padding: 0; }";
  content += ".controller li { margin: 0; padding: 0; padding-left: 50px; display: flex; justify-content: flex-end; }";
  content += ".controller li > div { display: flex; align-items: center; justify-content: space-between; flex: 1; }";
  content += ".controller li { margin: 0; }";
  content += ".controller li:first-child { margin-top: 10px; }";
  content += ".controller li:not(:last-child) { margin-bottom: 5px; }";
  content += ".controller a { width: 70px; text-align: center; }";
  content += ".on { background-color: hsl(121, 98%, 35%); }";
  content += ".on:hover { background-color: hsl(121, 98%, 25%);; }";
  content += ".off { background-color: hsl(358, 100%, 62%); }";
  content += ".off:hover { background-color: hsl(358, 100%, 42%); }";
  content += ".title { margin-right: 10px; }";
  content += ".container { width: 100%; min-height: 200px; padding: 20px; display: flex; align-items: center; flex-direction: column; margin-bottom: 5px; }";
  content += "</style></head>";
  content += "<body>";
  content += "<h1>Profile</h1>";
  content += "<div class='container'>";
  content += "<h2>Hello Roger-That</h2>";
  content += "<div class='controller'>";
  content += "<div class='item'>";
  content += "<div>LED Controller</div>";
  content += "<ul>";
  if (server.hasArg("led")) {
    if (server.arg("led") == "ON") {
      digitalWrite(0, HIGH);
      content += "<li><div><div class='title'>Turn LED:</div><a class='off' href='/profile?led=OFF'>OFF</a></div></li>";
    } else if (server.arg("led") == "OFF") {
      digitalWrite(0, LOW);
      content += "<li><div><div class='title'>Turn LED:</div><a class='on' href='/profile?led=ON'>ON</a></div></li>";
    }
  } else {
    if (digitalRead(0) == HIGH) {
      content += "<li><div><div class='title'>Turn LED:</div><a class='off' href='/profile?led=OFF'>OFF</a></div></li>";
    } else {
      content += "<li><div><div class='title'>Turn LED:</div><a class='on' href='/profile?led=ON'>ON</a></div></li>";
    }
  }
  content += "</ul>";
  content += "</div>";
  content += "</div>";
  content += "</div>";
  content += buildMenu();
  content += "</body>";
  content += "</html>";
  server.send(200, "text/html", content);
}

void publicPage() {
  String content = "<html>";
  content += "<head><style>";
  content += "* { box-sizing: border-box; margin: 0; padding: 0; }";
  content += "body { display: flex; flex-direction: column; align-items: center; padding-top: 30px; }";
  content += "h1 { text-transform: uppercase; }";
  content += "ul { list-style-type: none; display: flex; padding: 10px; }";
  content += "li:not(:last-child) { margin-right: 5px; }";
  content += "a { text-decoration: none; text-transform: capitalize; padding: 5px 15px; background-color: hsl(197, 100%, 53%); border-radius: 5px; color: white; }";
  content += "a:hover { background-color: hsl(197, 100%, 40%); }";
  content += ".container { width: 100%; min-height: 200px; padding: 20px; display: flex; align-items: center; flex-direction: column; margin-bottom: 5px; }";
  content += ".container img { width: 200px; border-radius: 100%; padding: 15px 0; }";
  content += ".container a { padding: 0; margin: 0; background: none; color: hsl(197, 100%, 53%); }";
  content += "</style></head>";
  content += "<body>";
  content += "<h1>Public</h1>";
  content += "<div class='container'>";
  content += "<p>Public Page</p>";
  content += "<img src='https://avatars.githubusercontent.com/u/32579177?v=4' alt='img'/>";
  content += "<p> Developed by <a target='_blank' href='https://github.com/Roger-Takeshita'>Roger Takeshita</a></p>";
  content += "</div>";
  content += buildMenu();
  content += "</body>";
  content += "</html>";
  server.send(200, "text/html", content);
}

void notFoundPage() {
  String content = "<html><body>";
  content += "<html>";
  content += "<head><style>";
  content += "* { box-sizing: border-box; margin: 0; padding: 0; }";
  content += "body { display: flex; flex-direction: column; align-items: center; padding-top: 30px; }";
  content += "h1 { text-transform: uppercase; }";
  content += "h2 { font-weight: 400; }";
  content += "ul { list-style-type: none; display: flex; padding: 10px; }";
  content += "li:not(:last-child) { margin-right: 5px; }";
  content += "a { text-decoration: none; text-transform: capitalize; padding: 5px 15px; background-color: hsl(197, 100%, 53%); border-radius: 5px; color: white; }";
  content += "a:hover { background-color: hsl(197, 100%, 40%); }";
  content += ".container { width: 100%; min-height: 200px; padding: 20px; display: flex; align-items: center; flex-direction: column; margin-bottom: 5px; }";
  content += ".container ul { display: block; }";
  content += ".item { display: flex; }";
  content += ".item div:first-child { width: 100px; }";
  content += ".item div:last-child { color: hsl(197, 100%, 53%); }";
  content += ".circle { list-style-type: circle; padding-left: 35px; }";
  content += ".circle li { color: blue; }";
  content += "</style></head>";
  content += "<body>";
  content += "<h1>Not Found</h1>";
  content += "<div class='container'>";
  content += "<h2>Not sure how you got here</h2>";
  content += "<ul>";
  content += "<li><div class='item'><div>URI:</div><div>" + server.uri() + "</div></div></li>";
  content += "<li><div class='item'><div>Method:</div><div>";
  content += (server.method() == HTTP_GET) ? "GET" : "POST";
  content += "</div></div></li>";
  if (server.args() > 0) {
    content += "<li><div class='item'><div>Argument(s):</div><div>" + String(server.args()) + "</div></div></li>";
    content += "<li><ul class='circle'>";
    for (uint8_t i = 0; i < server.args(); i++) {
      content += "<li>" + String(server.argName(i)) + ": " + String(server.arg(i)) + "</li>";
    }
    content += "</ul></li>";
  }
  content += "</ul>";
  content += "</div>";
  content += buildMenu();
  content += "</body>";
  content += "</html>";
  server.send(404, "text/html", content);
}

void setup() {
  Serial.begin(115200);
  pinMode(0, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_NAME);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", loginPage);
  server.on("/public", publicPage);
  server.on("/profile", profilePage);
  server.on("/logout", logout);

  server.onNotFound(notFoundPage);
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
