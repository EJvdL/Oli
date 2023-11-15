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
        Verbind aan het WiFI netwerk: %SSID%
        <br><br>Open je browser en ga naar 
        <ul>
        <li><b><a href="http://oli.local/status">http://oli.local/status</a></b> op een Apple apparaat of naar</li>
        <li><b><a href="http://%IP%/status">http://%IP%/status</a></b> op een Android apparaat</li>
        </ul>
        %COLOR%
    </fieldset>  
    <br><br>
    <fieldset>
        <a href="/config">Oli config</a>
        <br>
        <a href="/scenarios">Oli scenarios</a>
        <br>
        <a href="/colorPicker">Oli Kleuren tester</a>           
    </fieldset>
</body>
</html>
)=====";
