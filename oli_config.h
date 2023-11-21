const char PAGE_oli_config[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <script>
      function validateForm() {
        let SSID = document.forms["configForm"]["ssid"].value;
        let PWD  = document.forms["configForm"]["pwd"].value;

        if ((SSID == "" && PWD != "") || (SSID != "" && PWD == "")) {
          alert("Geen of beide velden SSID en Password invullen.");
          return false;
        }
      }
    </script>
  </head>
  <body>
    <h2>Oli config</h2>
    <form name="configForm" action="/submitConfig" onsubmit="return validateForm()" method="post" target="_self">
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
        <label for="ssid">Naam van het thuis netwerk</label><br>
        <input type="text" id="ssid" name="ssid"><br><br>
        <label for="pwd">Wachtwoord van thuis netwerk</label><br>
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
        <br>
        <a href="/colorPicker">Oli Kleuren tester</a>        
      </fieldset>
    </form>
  </body>
</html>
)=====";
