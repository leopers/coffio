const statusText = document.getElementById("status");

document.getElementById("makeCoffeeBtn").onclick = () => {
  fetch("/on")
    .then(() => updateStatus("☕ Coffee is brewing! Yay~"))
    .catch(() => updateStatus("⚠️ Couldn’t reach Coffio…"));
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
  statusText.classList.add("fade");
  setTimeout(() => {
    statusText.textContent = msg;
    statusText.classList.remove("fade");
  }, 200);
}
