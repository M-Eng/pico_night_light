#pragma once

#include "Global.h"
/**
 * @brief HTML assets for captive portal used by WiFiManager classes.
 */

const char hero_img[] PROGMEM = R"=====(
  data:image/png;base64,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qz959cUXPf13w3DJewZ6J550zNzcNDTmm7XlY09csPOOHZO1m7FfMQs37UqJHLMzmSbr86X5Q8CkJvfqSOxQkLVHJbAjZmJH3ik7OIZ38A6euXDknfOOHIMdeUeOnXPsHBWGDdjPiWfIMYZt27dPzU9pPWBVxAHomDf+w5tf8XjX1QguTFpsM1veb5+lY2ar0y557ukXPV+qQ44JGqFRNUJjTuGqDWihJo/cAB4kULU+hUYFIA0gSBgW3c2Xv+QNx2xrTRaxVZaFd86UiuPCOefcvA9/8BtnvOwN75baOwoEQexv2bxhy9YtKuIdO8feFt2ztz+OCucKZm976chUEDM8wzt1DG+/JRRMntkRHMExFY48w820C+fYMTki3xwchksdydkxjz0DR0wO7MgRM4MdObb9IJuG5dJ7iImcd9WwOufCCy9/2qOl6tvMbK2Hfu60S594yubD19x64/KDQUU1igbR6RAvPl2f91u/86QX/SVpSGNSTeqNWD+CnBpkdNTce5QvG9GicvaGWGQ4tenUM88//cCd37/5lkMHKqkNDxcNohfskNf//hN+88/ehWKzhj4xAQFS+07xra99a8+eve2yRaTs7AZh2ifpBttHYjIt5PK0UjJkF8Sa2tqZ6suJLSb19ine2TRvIA+haNIAmS5hCQDDgcEMgkN2QJs8tS1QLsOHY3ZM27ZsAAQi4ABh4lIGQ9765Jf848POedy7P/6Z627fuwINO7ZveMzjznnMU1+w5YQnoOorIoggcTQhQGFDDolcynMlr8SY901fr2as4rijKUwk9cLWk67464997dJ/++cvfOHrP7njgd5q2DDXuezRO19w5QuOOus5WrOGPjm27RdR4mLL5o2euSidReWkArhR/0MolESFbTKewZPOMtAu0TU0E6kpyRKlhBN77+FZHSeTQsa0SrUCqWFlapFLGC00N70r091yZq4kvIkAwBF77zZu6AI1EBOPQYWo0Fqodf7ZL/rXs1+0CKwCAkwABTTGwQqnZrGirCScm9fZORhNqm0wEdIGa0FGJMY9XSIoyDGzhhX47Ve88G+ueGENBCACDEwB0LgELBG7xuRYZeqmTbOO4JwnEk7Ug3VsUzJSjXKDUHEu3m4mJpnTKimkiimZzeIL5zyzc86OUuoYypp6N8GsNNLiU5r/kWJiK3nKw2sTU3SseM85Lsty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"
)=====";

const char lock_img[] PROGMEM = R"=====(
    data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAATZJREFUSEvdlb8uBHEUhb+jl0g0Eh0KrMcQQiIa4UUkGn8rFB6EaIUQj7GLQieikGj0R36bKTazM3N3Z1bBLed37/lyz725I345NIi+7Q3gGJjN8l+BQ0k3UX0IsL0HnJUI7Uq6qIJUAmyvAnfAB5BA95nYCnAOTAHLkh7LIBHgIQkAO5KuekVsbwOXwK2k9bqAL2ACGJf0nQNMAp/Au6TpugCnQkmFndqufO/WVg0oEojeCwG2N7OtmY9WMPf+lK3ude/3vg5svwGlngbQtqSlCND1tW7k51XUwf8FpOEdAanDdB7WimxsYtGCpOckansGSAevL5oAWpI6GWARaI8akCw6AMaAE2Br1ICBNreJRX8HkIaXhlgnOpJa0alIwzsF5oYkvAD7kqqP3ZCiYXr40w8VgoQf8KKEGdyIA9gAAAAASUVORK5CYII=
)=====";

const char root_template[] PROGMEM = R"=====(
<html>
<head>
    <meta name='viewport' content='width=device-width, initial-scale=1, minimum-scale=1'/>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #22272D;
        }

        .title {
            color: white;
            font-size: 28px;
            text-align: center;
        }

        .desc{
            color: #8293A6;
            font-size: 18px;
            text-align: center;
        }

        table {
            margin-left:auto;margin-right:auto;
        }

        .button {
            background-color: #22272D;
            border: #60BDC5;
            box-sizing: border-box;
            border-style: solid;
            border-width: 1px;
            border-radius: 4px;
            color: #8293A6;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 2px;
            transition-duration: 0.4s;
            cursor: pointer;
        }

        .button:hover {
            background-color: #60BDC5;
            color: white;
        }

        tr td:first-child {
           color: white;
           text-align: right;
           padding-right: 5px;
           font-size: 16px;
        }

        tr td {
           color: #8293A6;
           text-align: left;
           padding-left: 5px;
           font-size: 16px;
        }
      </style>
</head>
<body>
    <table>
        <tr>
            <td>
                <img src="${hero.img}" width="100px" alt="Hero logo"/>
            </td>
        </tr>
    </table>
    </div>
    <div class="title">Wifi Setup</div>
    <p/>
    <div class="desc">Configure the WiFi connection for the following device</div>
    <p/>
    <table>
        <tr>
            <td>Name</td>
            <td>${firmware.name}</td>
        </tr>
        <tr>
            <td>Maker</td>
            <td>${firmware.maker}</td>
        </tr>
        <tr>
            <td>Version</td>
            <td>${firmware.version}</td>
        </tr>
    </table>
    <p/>
    <table>
        <tr>
            <td>
                <a class="button" href="/wifi">Configure WiFi</a>
            </td>
        </tr>
    </table>
</body>
</html>
)=====";

const char wifi_template[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name='viewport' content='width=device-width, initial-scale=1, minimum-scale=1'/>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #22272D;
        }

        .title {
            color: white;
            font-size: 28px;
            text-align: center;
        }

        .desc{
            color: #8293A6;
            font-size: 18px;
            text-align: center;
        }

        table {
            margin-left:auto;margin-right:auto;
        }

        .button {
            background-color: #22272D;
            border: #60BDC5;
            border-style: solid;
            border-width: 1px;
            border-radius: 4px;
            box-sizing: border-box;
            color: #8293A6;
            cursor: pointer;
            display: inline-block;
            padding: 10px 32px;
            font-size: 16px;
            margin: 4px 2px;
            text-align: center;
            text-decoration: none;
            transition-duration: 0.4s;
        }

        .button:hover {
            background-color: #60BDC5;
            color: white;
        }

        tr td {
           color: white;
           padding: 5px;
           font-size: 16px;
        }

        a {
            color: #48c0c7
        }

        .sec {
            text-align: right;
            width: 80px;
        }

        /* From https://hungyi.net/posts/pure-css-signal-indicator/ */
        .signal-icon {
            height: 18px;
            width: 18px;
            /* To show you the power of flexbox! */
            display: flex;
            /* Bars should be placed left to right */
            flex-direction: row;
            /* Evenly space the bars with space in between */
            justify-content: space-between;
            /* Sink the bars to the bottom, so they go up in steps */
            align-items: baseline;
        }

        .signal-icon .signal-bar {
            /* 4 + 3 + 4 + 3 + 4 = 18px (as set above)
                4px per bar and 3px margins between */
            width: 4px;
            /* All bars faded by default */
            opacity: 30%;
            /* Choose a color */
            background: white;
         }

        /* 3 different heights for 3 different bars */
        .signal-icon .signal-bar:nth-child(1) { height: 40%; }
        .signal-icon .signal-bar:nth-child(2) { height: 70%; }
        .signal-icon .signal-bar:nth-child(3) { height: 100%; }

        /* Emphasize different bars depending on
        weak/medium/strong classes */
        .signal-icon.weak .signal-bar:nth-child(1),
        .signal-icon.medium .signal-bar:nth-child(1),
        .signal-icon.medium .signal-bar:nth-child(2),
        .signal-icon.strong .signal-bar:nth-child(1),
        .signal-icon.strong .signal-bar:nth-child(2),
        .signal-icon.strong .signal-bar:nth-child(3)
        { opacity: 100%; }

        input[type=text], input[type=password] {
            padding: 6px;
            margin:4px 0;
            width:100%;
        }

        form {
            text-align: center;
        }

        td.sec img#lock {
            content: url(${img.lock});
            width: 20px;
        }

        td.sec img#unlock {
            /*content: url(${img.unlock});*/ /* no icon shown for insecure WiFi */
            width: 20px;
        }
    </style>
    <script>
        function setSSID(e) {
            var ssid = e.innerHTML;
            document.getElementById('ssid').value = ssid;
        }
    </script>
</head>
<body>
    <table>
        <tr>
            <td>
                <img src="${hero.img}" width="100px" alt="Hero logo"/>
            </td>
        </tr>
    </table>
    </div>
    <div class="title">Wifi Setup</div>
    <p/>
    <div class="desc">Available WiFi Networks</div>
    <p/>
    <table>
        ${networks}
    </table>
    <p/>
    <br/>
    <table>
        <tr>
            <td>
            <div class="desc">WiFi Settings</div>
            </td>
        </tr>
    </table>
    <table>
        <tr>
            <td width="200px">
                <form method='POST' action='wifisave'>
                    <input id="ssid" type='text' placeholder='SSID' maxlength='32' name='n'/><br />
                    <input type='password' placeholder='Password' maxlength='32' name='p'/><br />
                    <input class="button" type='submit' value='Connect'/>
                </form>
            </td>
        </tr>
    </table>
    <table>
        <tr>
            <td>
                <p><a href='/'>Back to home</a></p>
            </td>
        </tr>
    </table>
</body>
</html>
)=====";

const char wifi_network_template[] PROGMEM = R"=====(
    <tr>
        <td>
            <div class="signal-icon ${signal}">
                <div class="signal-bar"></div>
                <div class="signal-bar"></div>
                <div class="signal-bar"></div>
            </div>
        </td>
        <td><a onclick="javascript:setSSID(this)" href="javascript:">${name}</a></td>
        <td class="sec">
            <img id="${network.security}"/>
        </td>
    </tr>
)=====";
