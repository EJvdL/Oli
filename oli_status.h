const char PAGE_oli_status[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta http-equiv="refresh" content="30">
</head>
<style>
table, th, td {
  border:1px solid black;
  border-collapse: collapse;
}
</style>
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
      <table style="width:100%">
      <tr>
        <th>Status</th>
        <th>LED</th> 
      </tr>      
      <tr>
        <td>Hardware fout</td>
        <td><b style="color:red;">Rood</b> 15 blink bij opstart</td>
      </tr>
     <tr>
        <td>Geen verbinding met een WiFi netwerk</td>
        <td style="color:orange;"><b>Oranje</b></td>
      </tr>
      <tr>
        <td>Verbinding met een WiFi netwerk</td>
        <td style="color:green;"><b>Groen</b></td>
      </tr>
      </table>
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
