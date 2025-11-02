const status = document.getElementById('status');
const ledIndicator = document.getElementById('ledIndicator');
const currentTimeElement = document.getElementById('currentTime');
const statusUrl = 'http://192.168.1.42/status';

function updateTime() {
    const now = new Date();
    const timeString = now.toLocaleTimeString('en-US', {
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
        hour12: true
    });
    currentTimeElement.textContent = timeString;
}

function updateStatus() {
    fetch(statusUrl)
        .then(response => response.json())
        .then(data => {
            const isLedOn = data.finalOutput === 0;  // Changed to 0 for ON state
            ledIndicator.className = 'led-indicator ' + (isLedOn ? 'on' : 'off');
            status.textContent = `LED Status: ${isLedOn ? 'ON' : 'OFF'}`;
        })
        .catch(err => {
            console.error('Fetch error:', err);
            status.textContent = 'LED Status: Disconnected';
            ledIndicator.className = 'led-indicator off';
        });
}

// Update time every second
setInterval(updateTime, 1000);

// Update LED status every 2 seconds
setInterval(updateStatus, 2000);

// Initial updates
updateTime();
updateStatus();
