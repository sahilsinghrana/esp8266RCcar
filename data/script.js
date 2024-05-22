window.oncontextmenu = function (event) {
    event.preventDefault();
    event.stopPropagation();
    return false;
  };

  function toggleFullScreen() {
    if (!document.fullscreenElement) {
      document.documentElement.requestFullscreen();
    } else if (document.exitFullscreen) {
      document.exitFullscreen();
    }
  }

  const steeringRange = document.getElementById("steeringRange");
  const driveRange = document.getElementById("driveRange");

  const stopBtn = document.getElementById("stopBtn");

  const hapticFeedback = () => {
    navigator.vibrate(500);
  };

  function callCommandApi(url, val) {
    return fetch(url, {
      method: "POST",
      body: val,
    }).then((res) => {
      console.log(res);
      hapticFeedback();
    });
  }

  function steerStraight() {
    return callCommandApi("/straight").then(() => {});
  }

  function steerLeft(val) {
    return callCommandApi("/left", val).then(() => {});
  }

  function steerRight(val) {
    return callCommandApi("/right", val).then(() => {});
  }

  function moveForward(val) {
    return callCommandApi("/forward", val).then(() => {});
  }

  function moveBackward(val) {
    return callCommandApi("/backward", val).then(() => {});
  }

  function stopMovement() {
    return callCommandApi("/stop").then(() => {});
  }

  const steerEl = document.getElementById("steer");
  const handleSteerChange = () => {
    const val = Number(event.target.value);

    if (val < 0) {
      // Steering left
      steerLeft(val);
      steerEl.innerText = `left-${val}`;
    } else if (val > 0) {
      steerRight(Math.abs(val));
      steerEl.innerText = `right-${Math.abs(val)}`;
    } else {
      steerEl.innerText = 0;
      steerStraight();
    }
  };

  const handleSteerRelease = () => {
    steerStraight();
    steeringRange.value = 0;
    steerEl.innerText = 0;
  };

  const speedEl = document.getElementById("speed");

  const handleDriveChange = () => {
    const val = Number(event.target.value);
    if (val > 0) {
      // Move Formward
      moveForward(val);
      speedEl.innerText = `forward-${val}`;
    } else if (val < 0) {
      moveBackward(Math.abs(val));
      speedEl.innerText = `reverse-${Math.abs(val)}`;
    } else {
      stopMovement();
      speedEl.innerText = 0;
    }
  };

  const handleDriveRelease = () => {
    stopMovement();
    driveRange.value = 0;
    speedEl.innerText = 0;
  };

  function initEventListners() {
    steeringRange.onchange = handleSteerChange;
    steeringRange.oninput = handleSteerChange;
    steeringRange.ontouchend = handleSteerRelease;

    driveRange.onchange = handleDriveChange;
    driveRange.oninput = handleDriveChange;
    driveRange.ontouchend = handleDriveRelease;
  }

  initEventListners();