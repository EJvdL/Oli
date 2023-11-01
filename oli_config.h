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
        <label for="oli-pwd">Password</label><br>
        <input type="password" minlength="8" maxlength="32" id="oli-pwd" name="oli-pwd">
    </fieldset>  
    <br><br>
    <fieldset>
    <legend>Gebruik eigen WiFi [optioneel]</legend><br>
        <label for="ssid">SSID van het thuis netwerk</label><br>
        <input type="text" id="ssid" name="ssid"><br><br>
        <label for="pwd">Password van thuis netwerk</label><br>
        <input type="password" minlength="8" maxlength="32" id="pwd" name="pwd"><br>
    </fieldset>
    <br><br>
    <fieldset>
    <legend>Terug naar fabrieksinstellingen</legend><br>
        <input type="checkbox" id="reset" name="reset">
        <label for="reset"> Terug naar fabrieksinstellingen</label><br>
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
<--!
TZ_Europe_Amsterdam	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Andorra	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Astrakhan	PSTR("<+04>-4")
TZ_Europe_Athens	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Belgrade	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Berlin	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Bratislava	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Brussels	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Bucharest	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Budapest	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Busingen	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Chisinau	PSTR("EET-2EEST,M3.5.0,M10.5.0/3")
TZ_Europe_Copenhagen	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Dublin	PSTR("IST-1GMT0,M10.5.0,M3.5.0/1")
TZ_Europe_Gibraltar	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Guernsey	PSTR("GMT0BST,M3.5.0/1,M10.5.0")
TZ_Europe_Helsinki	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Isle_of_Man	PSTR("GMT0BST,M3.5.0/1,M10.5.0")
TZ_Europe_Istanbul	PSTR("<+03>-3")
TZ_Europe_Jersey	PSTR("GMT0BST,M3.5.0/1,M10.5.0")
TZ_Europe_Kaliningrad	PSTR("EET-2")
TZ_Europe_Kiev	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Kirov	PSTR("<+03>-3")
TZ_Europe_Lisbon	PSTR("WET0WEST,M3.5.0/1,M10.5.0")
TZ_Europe_Ljubljana	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_London	PSTR("GMT0BST,M3.5.0/1,M10.5.0")
TZ_Europe_Luxembourg	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Madrid	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Malta	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Mariehamn	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Minsk	PSTR("<+03>-3")
TZ_Europe_Monaco	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Moscow	PSTR("MSK-3")
TZ_Europe_Oslo	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Paris	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Podgorica	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Prague	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Riga	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Rome	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Samara	PSTR("<+04>-4")
TZ_Europe_San_Marino	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Sarajevo	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Saratov	PSTR("<+04>-4")
TZ_Europe_Simferopol	PSTR("MSK-3")
TZ_Europe_Skopje	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Sofia	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Stockholm	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Tallinn	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Tirane	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Ulyanovsk	PSTR("<+04>-4")
TZ_Europe_Uzhgorod	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Vaduz	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Vatican	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Vienna	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Vilnius	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Volgograd	PSTR("<+03>-3")
TZ_Europe_Warsaw	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Zagreb	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
TZ_Europe_Zaporozhye	PSTR("EET-2EEST,M3.5.0/3,M10.5.0/4")
TZ_Europe_Zurich	PSTR("CET-1CEST,M3.5.0,M10.5.0/3")
-->
)=====";
