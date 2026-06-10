# Software Architecture

The system operates in three modes:

1. Calibration
2. Data Acquisition
3. Transfer

## Calibration Mode

The initial position is stored as reference.

## Acquisition Mode

The measured position is calculated using:

\[
x_{relative}=x_{current}-x_{initial}
\]

The data are stored as:

```cpp
data[2][n]

---

# software/bluetooth.md

```markdown
# Bluetooth Communication

The collected data are transmitted through Bluetooth to the Serial Bluetooth Terminal application.

![Bluetooth Terminal](assets/fig11.png)

*Figure 11 – Bluetooth application.*