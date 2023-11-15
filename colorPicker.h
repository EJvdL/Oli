const char PAGE_oli_color[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h2>Oli colorPicker</h2>
  <form action="/submitColor" method="post" target="_self">
    <fieldset>
        <input type="color" required id="K10" name="K10" value="%Color%"> 
        <br>
        %Color%
    </fieldset>  
    <br>
    <input type="submit">  
    <br><br>
    <fieldset>
      <a href="/config">Oli config</a>
      <br>    
      <a href="/status">Oli status</a>
      <br>
      <a href="/scenarios">Oli scenarios</a>
    </fieldset>    
  </form>
</body>
</html>
)=====";
