const statusText = document.getElementById("status");
let countdownInterval = null;

document.getElementById("makeCoffeeBtn").onclick = () => {
  fetch("/on")
    .then(() => startCountdown(30))
    .catch(() => updateStatus("⚠️ Failed to start brew."));
};

document.getElementById("scheduleBtn").onclick = () => {
  const time = document.getElementById("scheduleTime").value;
  if (!time) {
    updateStatus("📅 Please choose a time first!");
    return;
  }

  fetch(`/schedule?time=${encodeURIComponent(time)}`)
    .then(() => updateStatus(`🕐 Coffee scheduled for ${time}!`))
    .catch(() => updateStatus("⚠️ Couldn’t schedule…"));
};

function updateStatus(msg) {
  statusText.textContent = msg;
}

function startCountdown(seconds) {
  let remaining = seconds;

  updateStatus(`☕ Brewing... ${remaining}s remaining`);

  if (countdownInterval) clearInterval(countdownInterval);

  countdownInterval = setInterval(() => {
    remaining--;

    if (remaining > 0) {
      updateStatus(`☕ Brewing... ${remaining}s remaining`);
    } else {
      clearInterval(countdownInterval);
      updateStatus("✅ Brew complete!");
    }
  }, 1000);
}

document.getElementById("cancelBtn").onclick = () => {
  fetch("/cancel")
    .then(() => {
      if (countdownInterval) clearInterval(countdownInterval);
      updateStatus("🛑 Brew canceled.");
    })
    .catch(() => updateStatus("⚠️ Cancel failed."));
};
