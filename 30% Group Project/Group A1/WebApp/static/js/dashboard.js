// Global variables
let pointsChart = null;
let distributionChart = null;
let chartData = {
    labels: [],
    datasets: []
};

// Server-User mapping
const serverMapping = {
    'Afif': { server: 'server1', port: 5001, language: 'Python' },
    'Syahmi': { server: 'server2', port: 5002, language: 'Python' },
    'Irfan': { server: 'server3', port: 5003, language: 'Python' },
    'Hairiel': { server: 'server_c1', port: 6001, language: 'C' },
    'Faiz': { server: 'server_c2', port: 6002, language: 'C' }
};

// Update current time
function updateCurrentTime() {
    const now = new Date();
    document.getElementById('currentTime').textContent = now.toLocaleString();
}

// Fetch and display users data
async function fetchUsersData() {
    try {
        const response = await fetch('/api/users');
        const result = await response.json();
        
        if (result.success) {
            await updateUsersTable(result.data);
            updateCharts(result.data);
            document.getElementById('lastUpdate').textContent = result.timestamp;
        } else {
            console.error('Error fetching users:', result.error);
        }
    } catch (error) {
        console.error('Fetch error:', error);
    }
}

// Fetch and display statistics
async function fetchStats() {
    try {
        const response = await fetch('/api/stats');
        const result = await response.json();
        
        if (result.success) {
            const stats = result.data;
            document.getElementById('totalPoints').textContent = stats.total_points || 0;
            document.getElementById('avgPoints').textContent = (stats.avg_points || 0).toFixed(1);
            document.getElementById('maxPoints').textContent = stats.max_points || 0;
            document.getElementById('minPoints').textContent = stats.min_points || 0;
        }
    } catch (error) {
        console.error('Stats fetch error:', error);
    }
}

// Fetch and display server information
async function fetchServersInfo() {
    try {
        const response = await fetch('/api/servers');
        const result = await response.json();
        
        if (result.success) {
            updateServersInfo(result.data);
        }
    } catch (error) {
        console.error('Servers fetch error:', error);
    }
}

// Update users table
async function updateUsersTable(users) {
    const tbody = document.getElementById('usersTableBody');
    
    if (users.length === 0) {
        tbody.innerHTML = '<tr><td colspan="8" class="text-center">No data available</td></tr>';
        return;
    }
    
    let html = '';
    for (let index = 0; index < users.length; index++) {
        const user = users[index];
        const mapping = serverMapping[user.user] || { server: 'Unknown', port: '-', language: '-' };
        
        // Fetch user status
        let status = 'active';
        let statusBadge = '<span class="badge bg-success" id="status-' + user.user + '">🟢 Active</span>';
        try {
            const statusRes = await fetch('/api/users/' + user.user + '/status');
            const statusData = await statusRes.json();
            if (statusData.success) {
                status = statusData.status;
                statusBadge = status === 'active' 
                    ? '<span class="badge bg-success" id="status-' + user.user + '">🟢 Active</span>'
                    : '<span class="badge bg-warning text-dark" id="status-' + user.user + '">⏸️ Paused</span>';
            }
        } catch (e) {
            console.error('Error fetching status for ' + user.user, e);
        }
        
        html += `
            <tr>
                <td>${index + 1}</td>
                <td><strong>${user.user}</strong></td>
                <td><span class="badge bg-primary">${user.points}</span></td>
                <td>${user.datetime_stamp || 'N/A'}</td>
                <td>${mapping.server}:${mapping.port}</td>
                <td><span class="badge bg-info">${mapping.language}</span></td>
                <td>${statusBadge}</td>
                <td>
                    <button class="btn btn-sm btn-warning" onclick="toggleUser('${user.user}')" title="Pause/Resume">
                        <span id="toggle-icon-${user.user}">⏸️</span>
                    </button>
                    <button class="btn btn-sm btn-danger" onclick="resetPoints('${user.user}')" title="Reset Points">
                        🔄
                    </button>
                </td>
            </tr>
        `;
    }
    
    tbody.innerHTML = html;
}

// Update servers information
function updateServersInfo(servers) {
    const container = document.getElementById('serversInfo');
    
    let html = '';
    servers.forEach(server => {
        html += `
            <div class="col-md-4 mb-3">
                <div class="card">
                    <div class="card-body">
                        <h6 class="card-title">${server.name}</h6>
                        <p class="mb-1"><strong>User:</strong> ${server.user}</p>
                        <p class="mb-1"><strong>Port:</strong> ${server.port}</p>
                        <p class="mb-1"><strong>Language:</strong> 
                            <span class="badge ${server.language === 'Python' ? 'bg-info' : 'bg-warning'}">${server.language}</span>
                        </p>
                        <span class="badge bg-success">🟢 Running</span>
                    </div>
                </div>
            </div>
        `;
    });
    
    container.innerHTML = html;
}

// Initialize charts
function initCharts() {
    // Points Growth Chart (Line Chart)
    const ctx1 = document.getElementById('pointsChart').getContext('2d');
    pointsChart = new Chart(ctx1, {
        type: 'line',
        data: {
            labels: [],
            datasets: [
                {
                    label: 'Afif',
                    data: [],
                    borderColor: 'rgb(255, 99, 132)',
                    backgroundColor: 'rgba(255, 99, 132, 0.1)',
                    tension: 0.4
                },
                {
                    label: 'Syahmi',
                    data: [],
                    borderColor: 'rgb(54, 162, 235)',
                    backgroundColor: 'rgba(54, 162, 235, 0.1)',
                    tension: 0.4
                },
                {
                    label: 'Irfan',
                    data: [],
                    borderColor: 'rgb(255, 206, 86)',
                    backgroundColor: 'rgba(255, 206, 86, 0.1)',
                    tension: 0.4
                },
                {
                    label: 'Hairiel',
                    data: [],
                    borderColor: 'rgb(75, 192, 192)',
                    backgroundColor: 'rgba(75, 192, 192, 0.1)',
                    tension: 0.4
                },
                {
                    label: 'Faiz',
                    data: [],
                    borderColor: 'rgb(153, 102, 255)',
                    backgroundColor: 'rgba(153, 102, 255, 0.1)',
                    tension: 0.4
                }
            ]
        },
        options: {
            responsive: true,
            maintainAspectRatio: true,
            plugins: {
                legend: {
                    position: 'top',
                }
            },
            scales: {
                y: {
                    beginAtZero: true
                }
            }
        }
    });
    
    // Distribution Chart (Doughnut Chart)
    const ctx2 = document.getElementById('distributionChart').getContext('2d');
    distributionChart = new Chart(ctx2, {
        type: 'doughnut',
        data: {
            labels: ['Afif', 'Syahmi', 'Irfan', 'Hairiel', 'Faiz'],
            datasets: [{
                data: [0, 0, 0, 0, 0],
                backgroundColor: [
                    'rgb(255, 99, 132)',
                    'rgb(54, 162, 235)',
                    'rgb(255, 206, 86)',
                    'rgb(75, 192, 192)',
                    'rgb(153, 102, 255)'
                ]
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: true,
            plugins: {
                legend: {
                    position: 'bottom',
                }
            }
        }
    });
}

// Update charts with new data
function updateCharts(users) {
    const currentTime = new Date().toLocaleTimeString();
    
    // Update line chart
    if (pointsChart.data.labels.length >= 20) {
        pointsChart.data.labels.shift();
        pointsChart.data.datasets.forEach(dataset => dataset.data.shift());
    }
    
    pointsChart.data.labels.push(currentTime);
    
    users.forEach(user => {
        const datasetIndex = ['Afif', 'Syahmi', 'Irfan', 'Hairiel', 'Faiz'].indexOf(user.user);
        if (datasetIndex !== -1) {
            pointsChart.data.datasets[datasetIndex].data.push(user.points);
        }
    });
    
    pointsChart.update();
    
    // Update doughnut chart
    distributionChart.data.datasets[0].data = users.map(user => user.points);
    distributionChart.update();
}

// Refresh all data
function refreshData() {
    fetchUsersData();
    fetchStats();
    fetchServersInfo();
}

// Toggle user updates (pause/resume)
async function toggleUser(username) {
    try {
        const response = await fetch(`/api/users/${username}/toggle`, {
            method: 'POST'
        });
        const result = await response.json();
        
        if (result.success) {
            // Update status badge
            const statusBadge = document.getElementById(`status-${username}`);
            if (statusBadge) {
                if (result.status === 'active') {
                    statusBadge.className = 'badge bg-success';
                    statusBadge.textContent = '🟢 Active';
                } else {
                    statusBadge.className = 'badge bg-warning text-dark';
                    statusBadge.textContent = '⏸️ Paused';
                }
            }
            
            // Show success message
            showNotification(`${username} is now ${result.status}`, 'success');
        } else {
            showNotification(`Failed to toggle ${username}: ${result.error}`, 'danger');
        }
    } catch (error) {
        showNotification(`Error toggling ${username}: ${error.message}`, 'danger');
    }
}

// Reset user points
async function resetPoints(username) {
    if (!confirm(`Are you sure you want to reset points for ${username} to 0?`)) {
        return;
    }
    
    try {
        const response = await fetch(`/api/users/${username}/reset`, {
            method: 'POST'
        });
        const result = await response.json();
        
        if (result.success) {
            showNotification(`${username}'s points have been reset to 0`, 'success');
            // Immediately refresh the data
            setTimeout(refreshData, 500);
        } else {
            showNotification(`Failed to reset points: ${result.error}`, 'danger');
        }
    } catch (error) {
        showNotification(`Error resetting points: ${error.message}`, 'danger');
    }
}

// Show notification (Bootstrap toast or alert)
function showNotification(message, type = 'info') {
    // Create alert element
    const alertDiv = document.createElement('div');
    alertDiv.className = `alert alert-${type} alert-dismissible fade show position-fixed`;
    alertDiv.style.cssText = 'top: 80px; right: 20px; z-index: 9999; min-width: 300px;';
    alertDiv.innerHTML = `
        ${message}
        <button type="button" class="btn-close" data-bs-dismiss="alert"></button>
    `;
    
    document.body.appendChild(alertDiv);
    
    // Auto-remove after 3 seconds
    setTimeout(() => {
        alertDiv.remove();
    }, 3000);
}

// Initialize dashboard
document.addEventListener('DOMContentLoaded', function() {
    initCharts();
    updateCurrentTime();
    refreshData();
    
    // Auto-refresh every 5 seconds
    setInterval(refreshData, 5000);
    
    // Update time every second
    setInterval(updateCurrentTime, 1000);
});
