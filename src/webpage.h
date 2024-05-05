const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>raneX Car</title>
  </head>

  <style>
    * {
      box-sizing: border-box;
      -webkit-user-select: none; /* Safari */
      -ms-user-select: none; /* IE 10 and IE 11 */
      user-select: none; /* Standard syntax */
    }
    .staticFormButtonsWrapper,
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

    .inputButton {
      height: 3rem;
      width: 7rem;
    }
    body {
      background-color: black;
      color: white;
      text-align: center;
    }

    .restContainer {
      background-color: gray;
      margin-top: 3rem;
    }

    .restBtn {
      margin: 5px;
      height: 50px;
      width: 80px;
    }
  </style>

  <script>
    function onSubmit() {
      console.log("Submitted");
    }

    function onControlClick(command) {
      console.log("command : ", command);

      fetch("/control", {
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

    function onButtonRelease(command) {
      return;
      let newCommand = "";
      if (["FORWARD", "BACKWARD"].includes(command)) {
        newCommand = "STOP";
      } else if (["LEFT", "RIGHT"].includes(command)) {
        newCommand = "STRAIGHT";
      }
      fetch("/control", {
        method: "POST",
        body: newCommand,
      })
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    }
  </script>
  <body>
    <h1>raneX Car Controller</h1>
    <div class="restContainer">
      <button
        onmousedown="onControlClick('LEFT')"
        onmouseup="onButtonRelease('LEFT')"
        touchstart="onControlClick('LEFT')"
        touchend="onButtonRelease('LEFT')"
        class="restBtn"
        type="button"
      >
        Left
      </button>
      <button
        onmousedown="onControlClick('STRAIGHT')"
        onmouseup="onButtonRelease('STRAIGHT')"
        touchstart="onControlClick('STRAIGHT')"
        touchend="onButtonRelease('STRAIGHT')"
        class="restBtn"
        type="button"
      >
        Straight
      </button>
      <button
        onmousedown="onControlClick('RIGHT')"
        onmouseup="onButtonRelease('RIGHT')"
        touchstart="onControlClick('RIGHT')"
        touchend="onButtonRelease('RIGHT')"
        class="restBtn"
        type="button"
      >
        Right
      </button>
      <button
        onmousedown="onControlClick('STOP')"
        touchstart="onControlClick('STOP')"
        class="restBtn"
        class="touchendstBtn"
        type="button"
      >
        Stop
      </button>

      <div style="display: flex; flex-direction: column">
        <button
          onmousedown="onControlClick('FORWARD')"
          onmouseup="onButtonRelease('FORWARD')"
          touchstart="onControlClick('FORWARD')"
          touchend="onButtonRelease('FORWARD')"
          class="restBtn"
          type="button"
        >
          Forward
        </button>
        <button
          onmousedown="onControlClick('BACKWARD')"
          onmouseup="onButtonRelease('BACKWARD')"
          touchstart="onControlClick('BACKWARD')"
          touchend="onButtonRelease('BACKWARD')"
          class="restBtn"
          type="button"
        >
          Backward
        </button>
      </div>
    </div>
  </body>
</html>

)=====";