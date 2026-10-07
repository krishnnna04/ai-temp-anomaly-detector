# AI-Based Temperature Anomaly Detector

An Arduino project that detects abnormal temperature readings using a simple
machine learning approach (z-score anomaly detection). The model learns the
mean and standard deviation of normal temperature data in Python, and the
Arduino uses them to raise an alert when a reading is far from normal.

## Files
- `train_model.py`: learns MEAN and STD from normal temperature data
- `anomaly_detector.ino`: Arduino code that runs the anomaly detection and triggers the LED and buzzer alert

## How it works
1. Train: `train_model.py` calculates the mean and standard deviation of normal readings.
2. Deploy: these values are stored as constants in `anomaly_detector.ino`.
3. Detect: for each temperature reading, z = (temp - MEAN) / STD. If |z| is above 3, it is treated as an anomaly.

## Components
Arduino Uno, LM35 temperature sensor, LED, buzzer

## QA and tracking
Problems are tracked in GitHub Issues and planning is tracked on the GitHub Projects board.
