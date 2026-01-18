# 🎯 Quick Start Guide - Dashboard Controls

## Starting the System

```bash
# Start all services
cd d:\Xampp\htdocs\Docker
docker-compose --profile all up --build

# Wait for services to start (30 seconds)
# Open dashboard
http://localhost:8080
```

## Dashboard Controls

### Control Panel Location
Look for the **"Controls"** column in the user table:

```
┌─────┬─────────┬────────┬─────────────┬──────────┬──────────┬─────────┬──────────────┐
│  #  │  User   │ Points │ Last Update │  Server  │ Language │ Status  │   Controls   │
├─────┼─────────┼────────┼─────────────┼──────────┼──────────┼─────────┼──────────────┤
│  1  │ Afif    │  120   │ 2024-...    │ server1  │ Python   │ 🟢 Active│  [⏸️] [🔄]   │
└─────┴─────────┴────────┴─────────────┴──────────┴──────────┴─────────┴──────────────┘
```

### Button Functions

| Button | Function | Action |
|--------|----------|--------|
| ⏸️ | Pause/Resume | Toggle point updates |
| 🔄 | Reset | Set points to 0 |

## Usage Scenarios

### Scenario 1: Demonstrate Point Differences

**Goal**: Show that some users gain more points than others

1. **Pause all users first**:
   - Click ⏸️ button for Afif → Status: ⏸️ Paused
   - Click ⏸️ button for Syahmi → Status: ⏸️ Paused
   - Click ⏸️ button for Irfan → Status: ⏸️ Paused
   - Click ⏸️ button for Hairiel → Status: ⏸️ Paused
   - Click ⏸️ button for Faiz → Status: ⏸️ Paused
   - All points stop increasing

2. **Resume selected users**:
   - Click ⏸️ button for Afif again → Status: 🟢 Active
   - Click ⏸️ button for Irfan again → Status: 🟢 Active
   - Only Afif and Irfan gain points now

3. **Observe difference**:
   - Afif: 120 → 130 → 140 → 150 (increasing)
   - Syahmi: 80 (frozen)
   - Irfan: 90 → 100 → 110 → 120 (increasing)
   - Hairiel: 60 (frozen)
   - Faiz: 70 (frozen)

4. **Resume everyone**:
   - Click remaining ⏸️ buttons
   - All users catch up

### Scenario 2: Reset for Clean Demo

**Goal**: Start fresh demonstration with zero points

1. **Reset all users**:
   - Click 🔄 button for Afif
   - Confirm dialog: "Are you sure you want to reset points for Afif to 0?"
   - Click OK
   - Repeat for Syahmi, Irfan, Hairiel, Faiz

2. **Watch from zero**:
   - All points at 0
   - All active (🟢 Active)
   - Points grow together: 10, 20, 30, 40...

### Scenario 3: Focus on One User

**Goal**: Show single user behavior in isolation

1. **Pause everyone except one**:
   - Pause: Afif, Syahmi, Hairiel, Faiz
   - Keep Active: Irfan
   - Only Irfan's points increase

2. **Switch focus**:
   - Pause Irfan
   - Resume Hairiel
   - Now only Hairiel gains points

## Visual Indicators

### Status Badges

| Badge | Meaning |
|-------|---------|
| 🟢 Active | Points updating every 30 seconds |
| ⏸️ Paused | Points frozen, no updates |

### Notifications

After clicking controls, you'll see notifications:

```
✅ Afif is now paused
✅ Afif is now active  
✅ Afif's points have been reset to 0
❌ Failed to toggle Syahmi: Connection error
```

## Keyboard Shortcuts

None currently, but you can:
- Use Tab to navigate buttons
- Use Enter to click focused button
- Use Ctrl+R to refresh page

## Timing Information

| Event | Interval |
|-------|----------|
| Points Update | Every 30 seconds |
| Dashboard Refresh | Every 5 seconds |
| Status Check | Every 5 seconds (with data refresh) |

## API Alternative

### Using curl (for automation)

```bash
# Pause user
curl -X POST http://localhost:8080/api/users/Afif/toggle

# Check status
curl http://localhost:8080/api/users/Afif/status

# Reset points
curl -X POST http://localhost:8080/api/users/Afif/reset
```

### Using PowerShell

```powershell
# Pause user
Invoke-WebRequest -Uri "http://localhost:8080/api/users/Afif/toggle" -Method POST

# Check status
Invoke-RestMethod -Uri "http://localhost:8080/api/users/Afif/status"

# Reset points
Invoke-WebRequest -Uri "http://localhost:8080/api/users/Afif/reset" -Method POST
```

## Troubleshooting

### Problem: Button doesn't respond

**Solutions**:
1. Check browser console (F12) for JavaScript errors
2. Refresh page (Ctrl+R or F5)
3. Check server logs: `docker-compose logs web_dashboard`

### Problem: Status shows "Unknown"

**Solutions**:
1. Wait 5 seconds for next refresh cycle
2. Check control server logs:
   ```bash
   docker-compose logs server1 | grep "Control"
   ```
3. Verify control ports are running:
   ```bash
   curl http://localhost:6001/status
   ```

### Problem: Reset doesn't work

**Solutions**:
1. Check database connection:
   ```bash
   docker-compose logs database
   ```
2. Verify user exists:
   ```bash
   docker exec database mysql -udbuser -pdbpassword network_project \
     -e "SELECT * FROM user_tracking;"
   ```

## Tips for Best Demo

1. **Start Clean**: Reset all users to 0 before demo
2. **Explain First**: Show dashboard while all paused
3. **Gradual Enable**: Resume users one by one
4. **Highlight Differences**: Pause/resume to show control
5. **Monitor Charts**: Point to line chart for visual growth
6. **Use PhpMyAdmin**: Show database changes at http://localhost:8081

## Advanced Usage

### Create Point Gaps

```
1. Reset all users (all at 0)
2. Resume Afif only → runs 2 minutes → 40 points
3. Pause Afif
4. Resume Syahmi only → runs 1 minute → 20 points
5. Pause Syahmi
6. Resume Irfan only → runs 30 seconds → 10 points
7. Resume all → watch them grow with gaps:
   - Afif: 40 → 50 → 60 → 70
   - Syahmi: 20 → 30 → 40 → 50
   - Irfan: 10 → 20 → 30 → 40
```

### Simulate Server Issues

```
1. Pause specific user (e.g., Hairiel)
2. Tell audience "Server C1 is experiencing issues"
3. Show that others still work
4. Resume Hairiel
5. Tell audience "Server C1 recovered"
6. Show Hairiel catching up
```

## Summary

✅ **Pause/Resume**: Control updates without stopping containers  
✅ **Reset**: Start fresh with zero points  
✅ **Visual Feedback**: See status changes immediately  
✅ **No Commands**: All controls in web interface  
✅ **Perfect for Demos**: Show point differences clearly

---

**Quick Reference Card**

```
╔════════════════════════════════════╗
║  Dashboard Control Buttons         ║
╠════════════════════════════════════╣
║  ⏸️  = Pause/Resume Updates        ║
║  🔄  = Reset Points to 0           ║
║  🟢  = Active (updating)           ║
║  ⏸️  = Paused (frozen)             ║
╚════════════════════════════════════╝
```

**Need Help?**
- Check logs: `docker-compose logs <service>`
- View documentation: See README.md and CONTROL_FEATURES.md
- Test API: Use curl commands above
