const char PAGE_oli_status[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="refresh" content="30">
</head>
<body>
<h2>Oli Status</h2>
    <fieldset>
        %DATE_TIME%
        <br><br>
        %CONNECTED_TO% %SSID% 
        <br><br>Open je browser en ga naar 
        <ul>
        <li><b>oli.local</b> op een Apple apparaat of naar</li>
        <li><b>http://%IP%/</b> op een Android apparaat</li>
        </ul>
        %COLOR%
        <br>
        %INTENSITEIT%
    </fieldset>  
    <br><br>
    <fieldset>
        <a href="/config">Oli config</a>
        <br>
        <a href="/scenarios">Oli scenarios</a>
    </fieldset>
</body>
</html>
)=====";
