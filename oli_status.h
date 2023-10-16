const char PAGE_oli_status[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h2>Oli Status</h2>
    <fieldset>
        %DATE_TIME%
        <br><br>
        %CONNECTED_TO%
        <br><br>
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
