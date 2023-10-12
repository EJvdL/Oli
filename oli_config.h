const char PAGE_oli_config[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<h2>Oli config</h2>
<h1> Use the ESP WiFi manager library to solve the problem of local AP or STA with multiple credentials</h1>
<form action="/submitConfig" method="post" target="_self">
    <!--    post for sensitive data, action is empty, is this correct? -->
    <fieldset>
    <legend>Dag en tijd</legend>
        <label for="dag">Kies de dag van vandaag:</label>
        <select id="dag" name="dag">
            <option value="Maandag">Maandag</option>
            <option value="Dinsdag">Dinsdag</option>
            <option value="Woensdag">Woensdag</option>
            <option value="Donderdag">Donderdag</option>
            <option value="Vrijdag">Vrijdag</option>
            <option value="Zaterdag">Zaterdag</option>
            <option value="Zondag">Zondag</option>
        </select>
        <br>
        <br>
        <label for="tijd">Voer de tijd in</label>
        <input type="time" id="tijd" name="tijd">
    </fieldset>
    <br><br>
    <fieldset>
    <legend>Password</legend>  
        <label for="username">Username: Oli</label><br>
        <br>
        <label for="pwd">Password</label><br>
        <input type="password" id="pwd" name="pwd">
    </fieldset>  
    <br><br>
    <fieldset>
    <legend>Huis WiFi</legend>  
        <label for="ssid">SSID van het thuis netwerk</label><br>
        <input type="text" id="ssid" name="ssid"><br><br>
        <label for="pwd">Password van thuis netwerk</label><br>
        <input type="password" id="pwd" name="pwd"><br><br>
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
