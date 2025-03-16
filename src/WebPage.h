//---------------------------------------------------------------
// Our HTML webpage contents in program memory
// https://codepen.io/batuhanbas/pen/VwezONv

#include <Arduino.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<style>
body {
    background-color:black;
    color: gray;
    align-items: center;   
    }
</style>
</head>
<body>
<center>
<h1>Welcom to the Bootloder</h1>
<hr>
Click to <a href="http://<your_esp_ip>:8080/update">Update</a><br>
Click to <a href="http://<your_esp_ip>/wifi?">Configure</a>
</center>
</body>
</html>
)=====";
//---------------------------------------------------------------
