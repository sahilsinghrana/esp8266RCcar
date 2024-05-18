const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>raneX Car</title>

    <link rel="preconnect" href="https://fonts.googleapis.com" />
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
    <link
      href="https://fonts.googleapis.com/css2?family=Jaini&display=swap"
      rel="stylesheet"
    />
  </head>

  <style>
    :root {
      --th: 200;
      --bgh: 42;

      --primary: #f4f1deff;
      --accent: #e07a5fff;
      --dark: #3d405bff;
      --success: #81b29aff;
      --warning: #f2cc8fff;
    }
    * {
      box-sizing: border-box;
      -webkit-user-select: none;
      -ms-user-select: none;
      user-select: none;
    }

    h1 {
      font-family: "Jaini", system-ui;
      font-weight: 400;
      font-style: normal;
      font-size: 3rem;
      font-weight: 900;
      text-shadow: 4px 4px 2px rgba(0, 0, 0, 0.6);
      letter-spacing: 15px;
    }

    .restContainer {
      display: flex;
      justify-content: center;
      align-items: center;
      flex-wrap: wrap;
    }

    form {
      margin-left: 2em;
      margin-top: 2em;
    }

    body {
      background-color: var(--dark);
      color: var(--accent);
      text-align: center;
    }

    .restContainer {
      background-color: rgba(41, 119, 106, 0.098);
      padding: 5px;
      width: 100%;

      display: flex;
      justify-content: space-between;
      box-shadow: 0px -2px 40px 0px rgba(224, 122, 95, 1);
      border-radius: 12px;
      animation: rotateShadow 7s ease-out alternate-reverse infinite;
    }

    .steerBtn {
      width: 110px;
      height: 70px;
      background: rgba(0, 0, 0, 0.15);
      color: var(--accent);
      box-shadow: inset 1px 1px 11px 4px var(--warning);
    }

    .steerBtn:hover {
      box-shadow: inset 1px 1px 12px 10px var(--warning);
    }

    button {
      transition: box-shadow 800ms ease-in-out;
    }

    .leftBtn {
      clip-path: polygon(100% 100%, 100% 0, 0 50%);
    }

    .rightBtn {
      clip-path: polygon(0 0, 0 100%, 100% 50%);
    }

    .leftBtn.steerBtn:active {
      box-shadow: inset -20px 0px 20px 12px var(--accent);
    }

    .rightBtn.steerBtn:active {
      box-shadow: inset 20px 0px 20px 12px var(--accent);
    }

    .straightBtn {
      height: 50px;
      width: 90px;
      margin-bottom: 40px;
      background-color: black;
      color: var(--accent);
      clip-path: polygon(50% 0, 0 100%, 100% 100%);
      box-shadow: inset 1px 1px 12px 15px var(--warning);
    }

    .driveBtns {
      display: flex;
      flex-direction: column;
    }

    .driveBtn {
      background: rgba(0, 0, 0, 0.15);
      color: var(--acent);
      border: none;
      box-shadow: inset 1px 1px 11px 4px var(--warning);
      width: 80px;
    }

    .driveBtn[data-activated="true"] {
      background-color: var(--accent);
    }

    .steerBtn[data-activated="true"] {
      background-color: var(--accent);
    }

    .driveBtn:hover {
      box-shadow: inset 1px 1px 12px 10px var(--warning);
    }

    .forwardBtn.driveBtn:active {
      box-shadow: inset 0px -20px 20px 12px var(--accent);
    }

    .backwardBtn.driveBtn:active {
      box-shadow: inset 0px 20px 20px 12px var(--accent);
    }

    .forwardBtn {
      height: 90px;
      margin-bottom: 15px;
      clip-path: polygon(50% 0, 0 100%, 100% 100%);
    }

    .backwardBtn {
      height: 80px;
      clip-path: polygon(100% 0, 0 0, 50% 100%);
    }

    .driveController {
      display: flex;
      margin-right: 20px;
    }

    .stopBtn {
      align-self: flex-end;
      height: 50px;
      width: 60px;
      opacity: 0.8;
      background-color: red;
      color: white;
      margin-right: 10px;
      font-weight: 900;
      clip-path: polygon(
        30% 0%,
        70% 0%,
        100% 30%,
        100% 70%,
        70% 100%,
        30% 100%,
        0% 70%,
        0% 30%
      );
    }

    @keyframes rotateShadow {
      0% {
        box-shadow: 1px -3px 30px 0px rgba(224, 122, 95, 1);
      }

      25% {
        box-shadow: 5px 0px 10px 0px rgba(224, 122, 95, 1);
      }

      50% {
        box-shadow: 8px 10px 50px 0px rgba(224, 122, 95, 1);
      }

      100% {
        box-shadow: 2px 3px 20px 0px rgba(224, 122, 95, 1);
      }
    }

    label:before {
      content: attr(data-off);
    }

    [type="checkbox"]:checked + label:before {
      content: attr(data-on);
    }

    [type="checkbox"].lockCheckBox {
      display: none;
    }

    [type="checkbox"].lockCheckBox + label {
      cursor: pointer;
    }

    .lockLabel {
      display: inline-block;
      position: relative;
      --wb: 2ch;
      --wl: 5ch;
    }

    .lockLabel:after,
    .lockLabel:before {
      position: absolute;
      content: "";
      transition: 0.2s ease;
    }

    .lockLabel:before {
      content: "=";
      top: -0.5ch;
      left: 130%;
      width: var(--wb);
      height: 3ch;
      background-color: hsl(var(--th), 80%, 90%);
      border-radius: 0.25em;
      border: 1px solid hsl(var(--th), 80%, 40%, 30%);
      box-shadow: 0.1em 0.1em 0.1em #0005;
      display: grid;
      place-content: center;
      color: hsl(var(--th), 80%, 40%, 30%);
      z-index: 2;
    }

    .lockLabel:after {
      background-color: hsl(calc(var(--th) + 180), 80%, 70%);
      width: var(--wl);
      height: 2ch;
      top: calc(50% - 0.8ch);
      left: 130%;
      box-shadow: inset -0.05em -0.05em 0.2em 0 hsl(var(--bgh), 75%, 86%),
        inset 0.05em 0.05em 0.2em 0 hsl(var(--bgh), 25%, 26%);
      border-radius: 0.2em;
    }

    [type="checkbox"]:checked + .lockLabel:after {
      background-color: hsl(var(--th), 80%, 70%);
    }
    [type="checkbox"]:checked + .lockLabel:before {
      content: "=";
      left: calc(130% + (var(--wl) - var(--wb)));
    }
  </style>

  <body>
    <div class="container">
      <h1>CONTROLLER</h1>
      <div class="restContainer">
        <div class="steerBtns">
          <button
            class="straightBtn"
            id="straightBtn"
            onclick="steerStraight()"
            type="button"
          >
            &nbsp;
          </button>

          <div class="steering">
            <button class="leftBtn steerBtn" id="leftBtn" type="button">
              &nbsp;
            </button>

            <button class="rightBtn steerBtn" id="rightBtn" type="button">
              &nbsp;
            </button>
          </div>
        </div>
        <div>
          <input class="lockCheckBox" type="checkbox" id="lockCheckbox" />
          <label
            class="lockLabel"
            for="lockCheckbox"
            data-on="Lock"
            data-off="Unlock"
            >Lock</label
          >
        </div>
        <div class="driveController">
          <button
            class="stopBtn"
            onclick="stopMovement()"
            id="stopBtn"
            type="button"
          >
            STOP
          </button>
          <div class="driveBtns">
            <button class="forwardBtn driveBtn" id="forwardBtn" type="button">
              &nbsp;
            </button>
            <button class="backwardBtn driveBtn" id="backwardBtn" type="button">
              &nbsp;
            </button>
          </div>
        </div>
      </div>
    </div>
  </body>

  <script>
    window.oncontextmenu = function (event) {
      event.preventDefault();
      event.stopPropagation();
      return false;
    };

    const leftBtn = document.getElementById("leftBtn");
    const rightBtn = document.getElementById("rightBtn");
    const straightBtn = document.getElementById("straightBtn");

    const lockSwitch = document.getElementById("lockCheckbox");

    const isControllerLocked = () => {
      const isLocked = lockSwitch.checked;
      return isLocked;
    };

    lockSwitch.onclick = (e) => {
      initEventListners();
    };

    const stopBtn = document.getElementById("stopBtn");
    const forwardBtn = document.getElementById("forwardBtn");
    const backwardBtn = document.getElementById("backwardBtn");

    function callCommandApi(command) {
      return fetch("/control", {
        method: "POST",
        body: command,
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    }

    function steerStraight() {
      backwardBtn.dataset.activated = "false";
      callCommandApi("STRAIGHT");
    }

    function steerLeft() {
      rightBtn.dataset.activated = "false";
      callCommandApi("LEFT");
    }

    function steerRight() {
      leftBtn.dataset.activated = "false";
      callCommandApi("RIGHT");
    }

    function moveForward() {
      backwardBtn.dataset.activated = "false";
      callCommandApi("FORWARD");
    }

    function moveBackward() {
      forwardBtn.dataset.activated = "false";
      callCommandApi("BACKWARD");
    }

    function stopMovement() {
      forwardBtn.dataset.activated = "false";
      backwardBtn.dataset.activated = "false";
      callCommandApi("STOP");
    }

    const eventHandlerPressed =
      (clickStartHandler, clickReleaseHandler, element) => (event) => {
        event.preventDefault();
        if (isControllerLocked()) {
          if (element.dataset.activated === "true") {
            if (typeof clickReleaseHandler === "function") {
              clickReleaseHandler(event);
            }
            element.dataset.activated = "false";
            return;
          } else {
            element.dataset.activated = "true";
          }
        } else {
          element.dataset.activated = "false";
        }

        if (typeof clickStartHandler === "function") {
          clickStartHandler(event);
        }
      };

    const eventHandlerReleased = (handler, element) => (event) => {
      // event.preventDefault();
      if (!isControllerLocked()) {
        if (typeof handler === "function") {
          handler(event);
        }
      }
    };

    function addActionEvents(element, clickStartHandler, clickReleaseHandler) {
      if (!element) {
        throw new Error("No Element");
      }
      if (clickStartHandler) {
        element.ontouchstart = eventHandlerPressed(
          clickStartHandler,
          clickReleaseHandler,
          element
        );
        element.onmousedown = eventHandlerPressed(
          clickStartHandler,
          clickReleaseHandler,
          element
        );
      }

      if (clickReleaseHandler) {
        element.onmouseup = eventHandlerReleased(clickReleaseHandler, element);
        element.ontouchcancel = eventHandlerReleased(
          clickReleaseHandler,
          element
        );
        element.ontouchend = eventHandlerReleased(clickReleaseHandler, element);
      }
    }

    function toggleLock(e) {
      console.log("checked", e);
    }

    function initEventListners() {
      addActionEvents(leftBtn, steerLeft, steerStraight);
      addActionEvents(rightBtn, steerRight, steerStraight);

      addActionEvents(forwardBtn, moveForward, stopMovement);
      addActionEvents(backwardBtn, moveBackward, stopMovement);
    }

    initEventListners();
  </script>
</html>

)=====";