# RasoOnline Load Testing Tools

This directory contains scripts for running load tests against rasoonline.com using Vegeta and collecting results in Excel/CSV format.

## Quick Start

```powershell
# 1. Run a full test suite (2m per stage @ 10-150 RPS)
.\run_tests.bat

# 2. Check results.xlsx for the consolidated data
```

## Available Scripts

### Test Runners

- `run_tests.bat`: Main test suite
  - Runs 5 stages: 10, 30, 60, 100, 150 RPS for 2 minutes each
  - Creates JSON output for each stage
  - Automatically updates results.xlsx
  - Usage: `.\run_tests.bat`

- `raso_ramp.ps1`: Ramp-up test
  - Gradually increases load from 10 to 200 RPS
  - Saves detailed metrics and plots
  - Usage: `.\raso_ramp.ps1`

- `rasoonline_test.bat`: Interactive menu
  - Menu-driven test selection
  - Options for quick/moderate/stress tests
  - Usage: `.\rasoonline_test.bat`

### Data Processing

- `fill_excel.ps1`: Process Vegeta JSON output
  - Converts test results to Excel rows
  - Creates Excel file if missing
  - Usage:
    ```powershell
    # Basic: process a JSON file
    .\fill_excel.ps1 "results_stress.json" "results.xlsx"

    # With test name/label
    .\fill_excel.ps1 "Stress Test (80 RPS)" "results_stress.json" "results.xlsx"
    ```

## File Structure

```
c:\tools\
├── results\            # Test result files
│   └── ramp\          # Ramp test outputs
├── *.json             # Test result JSON files
├── results.xlsx       # Consolidated results
├── url.txt           # Target URLs for testing
└── *.bat/*.ps1       # Test runners and processors
```

## Common Tasks

### 1. Run a Quick Smoke Test

```powershell
# Create url.txt if needed
echo GET https://rasoonline.com/ > url.txt

# Run 20s test at 10 RPS
vegeta attack -rate 10 -duration 20s -targets=url.txt | vegeta report -type=json > smoke_10.json

# Add to results
.\fill_excel.ps1 "Smoke Test" "smoke_10.json" "results.xlsx"
```

### 2. Run Full Test Suite

```batch
run_tests.bat
```

This will:
- Create url.txt if missing
- Run 5 stages (10-150 RPS)
- Save JSON for each stage
- Update results.xlsx

### 3. Run Custom Test

```powershell
# Set parameters
$RATE = 50        # requests per second
$DURATION = "30s" # test duration
$NAME = "Custom Test ($RATE RPS)"

# Run test and capture JSON
vegeta attack -rate $RATE -duration $DURATION -targets=url.txt | `
    vegeta report -type=json > "custom_$RATE.json"

# Add to results
.\fill_excel.ps1 $NAME "custom_$RATE.json" "results.xlsx"
```

## Understanding Results

The Excel file (results.xlsx) contains these metrics for each test:

- Name: Test identifier/label
- Rate: Target requests per second
- Requests: Total requests made
- SuccessPct: Percentage of successful requests
- MeanMs: Mean latency in milliseconds
- P95ms: 95th percentile latency
- P99ms: 99th percentile latency
- Throughput: Actual requests/second achieved
- Errors: Count of failed requests

## Troubleshooting

1. If Excel fails to update:
   - Ensure Excel is installed
   - Try closing any open Excel instances
   - Check file permissions on results.xlsx

2. If tests fail:
   - Verify url.txt exists and contains valid URLs
   - Check network connectivity to rasoonline.com
   - Ensure vegeta.exe is in PATH

## Next Steps

Consider:
1. Running the full test suite with `run_tests.bat`
2. Examining results.xlsx for performance trends
3. Using raso_ramp.ps1 for gradual load increase
4. Creating custom test configurations in url.txt