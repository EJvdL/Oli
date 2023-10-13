const char PAGE_oli_config[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h2>Oli config</h2>
<form action="/submitConfig" method="post" target="_self">
    <fieldset>
    <legend>Datum en tijd</legend><br>
      <label for="datetime">Huidige datum en tijd</label>
      <input type="datetime-local" id="datetime" name="datetime">         
    </fieldset>
    <br><br>
    <fieldset>
    <legend>Wijzig Oli password [optioneel]</legend><br>
        <label for="pwd">Password</label><br>
        <input type="password" id="pwd" name="pwd">
    </fieldset>  
    <br><br>
    <fieldset>
    <legend>Gebruik eigen WiFi [optioneel]</legend><br>
        <label for="ssid">SSID van het thuis netwerk</label><br>
        <input type="text" id="ssid" name="ssid"><br><br>
        <label for="pwd">Password van thuis netwerk</label><br>
        <input type="password" id="pwd" name="pwd"><br>
    </fieldset>
    <br><br>    
    <input type="submit">  
    <br><br>
    <fieldset>
    <a href="/status">Oli status</a>
    <br>
    <a href="/scenarios">Oli scenarios</a>
    </fieldset>
</form>
</body>
</html>
)=====";
