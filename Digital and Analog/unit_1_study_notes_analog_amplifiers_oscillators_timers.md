# Unit 1: Analog Amplifiers, Oscillators & Timers (9 Hours)

---

## 1. Amplifier Classification

Power amplifiers are large-signal amplifiers designed to deliver significant power to low-impedance loads (such as speakers or RF antennas). They are classified based on the **conduction angle ($\theta$)**—the portion of the input signal cycle during which the active transistor conducts current.

### 1.1 Fundamental Operational Concepts & Profiles

#### **Class-A Power Amplifier**
* **Q-Point Location:** Biased right at the center of the AC load line.
* **Conduction Angle:** $\theta = 360^\circ$ ($2\pi$ radians). The transistor conducts for the entire cycle of the input signal.
* **Operational Concept:** Because the transistor is always ON, there is a continuous DC bias current ($I_{CQ}$) flowing even when no input signal is present.
* **Power & Efficiency Profile:** 
  * Constant power dissipation from the DC supply regardless of input signal amplitude.
  * **Maximum Theoretical Efficiency ($\eta_{\max}$):**
    * Series-fed (Resistive load): $25\%$
    * Transformer-coupled load: $50\%$
* **Characteristics:** Highest linearity and lowest distortion, but suffers from heavy thermal dissipation and poor efficiency.

#### **Class-B Power Amplifier**
* **Q-Point Location:** Biased exactly at the cutoff point on the load line ($I_{CQ} = 0$).
* **Conduction Angle:** $\theta = 180^\circ$ ($\pi$ radians). The transistor conducts for only half of the input signal cycle.
* **Operational Concept:** Typically implemented in a **push-pull configuration** using two complementary transistors (one NPN, one PNP)—one amplifies the positive half-cycle and the other amplifies the negative half-cycle.
* **Power & Efficiency Profile:**
  * Zero static power dissipation when no input signal is present.
  * **Maximum Theoretical Efficiency ($\eta_{\max}$):** $\frac{\pi}{4} \approx 78.5\%$
* **Characteristics:** Suffers from **crossover distortion** due to the dead zone between $-0.7\text{ V}$ and $+0.7\text{ V}$ (base-emitter cut-in voltage $V_{BE}$), where neither transistor conducts.

#### **Class-AB Power Amplifier**
* **Q-Point Location:** Biased slightly above cutoff, just into the active region.
* **Conduction Angle:** $180^\circ < \theta < 360^\circ$.
* **Operational Concept:** Designed to eliminate the crossover distortion of Class-B amplifiers. A small quiescent current flows through both push-pull transistors using diode biasing or a $V_{BE}$ multiplier.
* **Power & Efficiency Profile:**
  * **Maximum Theoretical Efficiency ($\eta_{\max}$):** Between $50\%$ and $78.5\%$.
* **Characteristics:** Combines the good linearity of Class-A with the high efficiency of Class-B. Most widely used topology in audio power amplification.

#### **Class-C Power Amplifier**
* **Q-Point Location:** Biased well below cutoff (negative base-emitter bias for NPN).
* **Conduction Angle:** $\theta < 180^\circ$ (typically $90^\circ$ to $120^\circ$).
* **Operational Concept:** The transistor conducts only during the peak positive portion of the input cycle, producing narrow current pulses. A parallel $LC$ resonant tank circuit at the collector filters out harmonics and restores a full sinusoidal waveform at the resonant frequency.
* **Power & Efficiency Profile:**
  * **Maximum Theoretical Efficiency ($\eta_{\max}$):** $> 80\%$ (approaches $90\%+$ as $\theta \to 0$).
* **Characteristics:** Highly non-linear; unsuitable for audio amplification. Used extensively in high-frequency Radio Frequency (RF) transmitters and tuned amplifiers.

---

### 1.2 Key Power Metrics & Equations

1. **DC Input Power ($P_{DC}$):** Power drawn from the power supply $V_{CC}$.
   $$P_{DC} = V_{CC} \cdot I_{DC}$$
2. **AC Output Power ($P_{ac}$):** Power delivered to the load resistor $R_L$.
   $$P_{ac} = I_{rms}^2 R_L = \frac{V_{rms}^2}{R_L} = \frac{V_m I_m}{2} = \frac{V_{p-p}^2}{8 R_L}$$
   *(where $V_m$ and $I_m$ are peak output voltage and current, and $V_{p-p}$ is peak-to-peak voltage).*
3. **Power Dissipation ($P_d$):** Power lost as heat in the active device(s).
   $$P_d = P_{DC} - P_{ac}$$
4. **Collector/Amplifier Efficiency ($\eta$):**
   $$\eta\% = \left( \frac{P_{ac}}{P_{DC}} \right) \times 100\%$$

### 1.3 Summary Comparison Table

| Parameter | Class-A | Class-B | Class-AB | Class-C |
| :--- | :--- | :--- | :--- | :--- |
| **Conduction Angle ($\theta$)** | $360^\circ$ | $180^\circ$ | $180^\circ < \theta < 360^\circ$ | $< 180^\circ$ |
| **Q-Point Position** | Center of load line | At Cutoff | Just above Cutoff | Below Cutoff |
| **Max Efficiency ($\eta_{\max}$)** | $25\%$ (direct) / $50\%$ (transformer) | $78.5\%$ | $50\% - 78.5\%$ | $> 80\%$ |
| **Signal Distortion** | None (Minimal) | Crossover Distortion | Low | Very High |
| **Primary Application** | Low-power audio, pre-amps | Push-pull audio stages | High-fidelity audio amps | RF tuned amplifiers |

---

## 2. Feedback & Oscillation Recap

### 2.1 Mechanics of Feedback Loop Topologies
A closed-loop feedback system takes a fraction of the output signal $X_o$ via a feedback network ($\beta$) and combines it with the external input signal $X_s$.

* **Open-Loop Gain:** $A$
* **Feedback Factor:** $\beta = \frac{X_f}{X_o}$
* **Loop Gain:** $T = A\beta$

#### **Negative Feedback (Degenerative)**
The feedback signal is $180^\circ$ out of phase with the input signal ($X_i = X_s - X_f$).
$$A_f = \frac{A}{1 + A\beta}$$
* **Effects:** Stabilizes gain against component variations, increases bandwidth, reduces non-linear distortion, and modifies input/output impedances.

#### **Positive Feedback (Regenerative)**
The feedback signal is in phase with the input signal ($X_i = X_s + X_f$).
$$A_f = \frac{A}{1 - A\beta}$$
* **Effects:** Increases overall gain, decreases bandwidth, and leads to instability/oscillations when $A\beta \ge 1$. Forms the basis for oscillators and bistable/astable switching circuits (Schmitt triggers, multivibrators).

#### **Four Basic Negative Feedback Topologies:**
| Topology | Input Mixing | Output Sampling | Input Impedance ($Z_{if}$) | Output Impedance ($Z_{of}$) |
| :--- | :--- | :--- | :--- | :--- |
| **Voltage-Series** (Series-Shunt) | Series (Voltage) | Shunt (Voltage) | Increases: $Z_i(1+A\beta)$ | Decreases: $\frac{Z_o}{1+A\beta}$ |
| **Current-Series** (Series-Series) | Series (Voltage) | Series (Current) | Increases: $Z_i(1+A\beta)$ | Increases: $Z_o(1+A\beta)$ |
| **Voltage-Shunt** (Shunt-Shunt) | Shunt (Current) | Shunt (Voltage) | Decreases: $\frac{Z_i}{1+A\beta}$ | Decreases: $\frac{Z_o}{1+A\beta}$ |
| **Current-Shunt** (Shunt-Series) | Shunt (Current) | Series (Current) | Decreases: $\frac{Z_i}{1+A\beta}$ | Increases: $Z_o(1+A\beta)$ |

---

### 2.2 Core Criteria for Sustained Oscillation (Barkhausen Criterion)
For a positive feedback circuit to generate a continuous, undamped sinusoidal output without any external input signal ($X_s = 0$), the denominator of the closed-loop gain equation $1 - A\beta$ must equal zero:
$$A\beta = 1 \implies |A\beta| \angle \phi_{\text{loop}} = 1 \angle 0^\circ$$

This gives the two fundamental conditions known as the **Barkhausen Criterion**:
1. **Magnitude Condition:** The magnitude of the loop gain must be unity:
   $$|A\beta| = 1$$
   *(Note: In practical circuits, $|A\beta|$ is designed to be slightly greater than $1$—typically $1.05$ to $1.1$—to ensure oscillations start up from thermal noise, and non-linearities later limit the amplitude so $|A\beta| = 1$ in steady state).*
2. **Phase Condition:** The total phase shift around the closed loop must be $0^\circ$ or an integral multiple of $360^\circ$:
   $$\angle A\beta = 0^\circ \text{ or } 360^\circ n \quad (n = 1, 2, 3\dots)$$

---

## 3. Oscillator Circuits

Audio Frequency (AF) oscillators typically use $RC$ feedback networks because $LC$ components become impractically bulky and expensive at low frequencies.

### 3.1 RC Phase Shift Oscillator

#### **Structural Design**
* Consists of an **inverting amplifier** (Op-Amp in inverting mode or Common-Emitter BJT stage) and a feedback network made of **three cascaded $RC$ sections**.
* The inverting amplifier provides a fixed phase shift of $180^\circ$.
* To satisfy the Barkhausen phase condition ($360^\circ$ total), the $3$-stage $RC$ ladder network must provide an additional **$180^\circ$ phase shift** (approx. $60^\circ$ per stage) at a single specific frequency $f_o$.

```
         +--------- Rf ---------+
         |                      |
         |    |\                |
    +----+----|-\               |
    |         |  \______________+______ Vo
    |     +---|+/               |
    |     |   |/                |
    |    GND                    |
    |                           |
    +---R---C---+---R---C---+---C---+
                |           |       |
                R           R       R (or Op-Amp Input R1)
                |           |       |
               GND         GND     GND
```

#### **Mathematical Equations & Operation (Op-Amp Implementation)**
1. **Frequency of Oscillation ($f_o$):**
   $$f_o = \frac{1}{2\pi R C \sqrt{6}}$$
2. **Feedback Factor ($\beta$) at $f_o$:**
   At $f_o$, the attenuation of the $3$-stage $RC$ ladder network is:
   $$\beta = -\frac{1}{29} \implies |\beta| = \frac{1}{29}$$
   *(The negative sign indicates the $180^\circ$ phase shift).*
3. **Gain Condition for Sustained Oscillation:**
   Since $|A\beta| \ge 1$ and $|\beta| = \frac{1}{29}$:
   $$|A_v| = \frac{R_f}{R_1} \ge 29$$

*(Note: For a BJT-based RC Phase Shift oscillator where the collector load resistor $R_C$ is comparable to $R$, the formulas modify to $f_o = \frac{1}{2\pi R C \sqrt{6 + 4k}}$ and $h_{fe} \ge 23 + 29k + \frac{4}{k}$, where $k = \frac{R_C}{R}$).*

---

### 3.2 Wien Bridge Oscillator

#### **Structural Design**
* Uses a **non-inverting Op-Amp amplifier** (which introduces $0^\circ$ phase shift) and a **lead-lag $RC$ bridge network**.
* **Positive Feedback Path (Lead-Lag Network):** A series $R_1 C_1$ combination connected to a parallel $R_2 C_2$ combination (usually $R_1 = R_2 = R$ and $C_1 = C_2 = C$). At high frequencies, it acts as a lag network; at low frequencies, it acts as a lead network. At the resonant frequency $f_o$, the phase shift is exactly **$0^\circ$**.
* **Negative Feedback Path (Voltage Divider):** Resistors $R_f$ and $R_i$ set the closed-loop voltage gain of the non-inverting amplifier.

```
                  +------- C ------- R -------+
                  |                           |
                  +------------+              |
                  |            |              |
                  R            C              |
                  |            |   |\         |
                 GND          GND  | \        |
                               +---|+\        |
                                   |  \_______+______ Vo
                               +---|-\        |
                               |   | /        |
                               |   |/         |
                               |              |
                  +---- Ri ----+----- Rf -----+
                  |
                 GND
```

#### **Mathematical Equations & Operation**
1. **Frequency of Oscillation ($f_o$):**
   For unequal components:
   $$f_o = \frac{1}{2\pi \sqrt{R_1 R_2 C_1 C_2}}$$
   For matched components ($R_1 = R_2 = R$ and $C_1 = C_2 = C$):
   $$f_o = \frac{1}{2\pi R C}$$
2. **Feedback Factor ($\beta$) at $f_o$:**
   At $f_o$, the voltage transfer ratio of the lead-lag network is:
   $$\beta = \frac{1}{3} \angle 0^\circ$$
3. **Gain Condition for Sustained Oscillation:**
   To satisfy $|A\beta| \ge 1$, the non-inverting amplifier gain must be:
   $$A_v = 1 + \frac{R_f}{R_i} \ge 3 \implies \frac{R_f}{R_i} \ge 2 \implies R_f \ge 2 R_i$$
* **Amplitude Stabilization:** Often incorporates a non-linear element like a tungsten lamp (PTC thermistor) in place of $R_i$ or antiparallel diodes across $R_f$ to automatically adjust gain to $3$ as amplitude grows.

---

## 4. Multivibrators

Multivibrators are two-state regenerative switching circuits that generate non-sinusoidal rectangular or square waveforms.

### 4.1 Astable Multivibrator (Free-Running)
* **State Profile:** Has **no stable states** (two quasi-stable states). It continuously oscillates between HIGH ($+V_{\text{sat}}$) and LOW ($-V_{\text{sat}}$) without any external trigger.

#### **Op-Amp Astable Operation**
* **Positive Feedback:** Resistors $R_1$ and $R_2$ form a voltage divider feeding back a fraction $\beta = \frac{R_2}{R_1 + R_2}$ of $V_o$ to the non-inverting terminal ($V_+$). This sets two threshold voltages:
  * Upper Threshold: $V_{UT} = +\beta V_{\text{sat}}$
  * Lower Threshold: $V_{LT} = -\beta V_{\text{sat}}$
* **Negative Feedback ($RC$ Timing):** Resistor $R$ and capacitor $C$ are connected in the inverting path.
* **Cycle Mechanics:**
  1. Assume $V_o = +V_{\text{sat}}$. Then $V_+ = +\beta V_{\text{sat}}$.
  2. Capacitor $C$ charges exponentially toward $+V_{\text{sat}}$ through resistor $R$ with time constant $\tau = RC$.
  3. The instant the capacitor voltage $V_C$ (at $V_-$) exceeds $V_{UT} = +\beta V_{\text{sat}}$, the Op-Amp output immediately switches to $-V_{\text{sat}}$.
  4. Now $V_+ = -\beta V_{\text{sat}}$, and $C$ begins discharging and charging toward $-V_{\text{sat}}$ until $V_C$ drops below $V_{LT}$, repeating the cycle infinitely.

#### **Timing Equations:**
* **Time Period ($T$):**
  $$T = 2 R C \ln\left(\frac{1 + \beta}{1 - \beta}\right) = 2 R C \ln\left(1 + \frac{2 R_2}{R_1}\right)$$
* **Special Case:** If $R_1 = 1.16 R_2$, then $\ln\left(1 + \frac{2R_2}{R_1}\right) = 1$, simplifying the period to:
  $$T = 2 R C \quad \text{and} \quad f = \frac{1}{2RC}$$

---

### 4.2 Monostable Multivibrator (One-Shot)
* **State Profile:** Has **one permanent stable state** and **one quasi-stable state**. It remains in its stable state until an external trigger pulse forces it into the quasi-stable state for a fixed duration $T$, after which it automatically returns to the stable state.

#### **Op-Amp Monostable Operation**
* **Circuit Modification:** Built similarly to the astable circuit, except a clamping diode $D_1$ is placed in parallel with capacitor $C$ (cathode to ground, anode to $V_-$).
* **Stable State:** Output is at $+V_{\text{sat}}$. Diode $D_1$ is forward-biased, clamping the capacitor voltage at $V_C \approx +0.7\text{ V}$ ($V_D$). Meanwhile, $V_+ = +\beta V_{\text{sat}}$. Since $V_+ > V_-$, the state is stable.
* **Quasi-Stable State (Triggered):**
  1. A negative trigger pulse applied to $V_+$ brings $V_+$ below $+0.7\text{ V}$, flipping the output to $V_o = -V_{\text{sat}}$.
  2. Now $V_+ = -\beta V_{\text{sat}}$, and diode $D_1$ becomes reverse-biased (open circuit).
  3. Capacitor $C$ discharges from $+0.7\text{ V}$ and charges exponentially toward $-V_{\text{sat}}$ via resistor $R$.
  4. Once $V_C$ reaches $-\beta V_{\text{sat}}$, the Op-Amp switches back to $+V_{\text{sat}}$ (stable state).

#### **Pulse Width Equation ($T$):**
$$T = R C \ln\left( \frac{1 + \frac{V_D}{V_{\text{sat}}}}{1 - \beta} \right)$$
If $V_{\text{sat}} \gg V_D$ (ignoring diode drop):
$$T = R C \ln\left( \frac{1}{1 - \beta} \right) = R C \ln\left( 1 + \frac{R_2}{R_1} \right)$$
If $R_1 = R_2$ ($\beta = 0.5$):
$$T = R C \ln(2) \approx 0.693 R C$$

---

## 5. Wave-Shaping & Timing Blocks

### 5.1 Schmitt Trigger (Regenerative Comparator)

#### **Internal Architecture & Hysteresis Mechanics**
* A Schmitt Trigger is a comparator with **positive feedback**. It converts an irregular, slow-varying, or noisy analog waveform into a clean, sharp square/rectangular wave.
* Because of positive feedback, the circuit exhibits **Hysteresis**—a dead-band between two distinct switching thresholds:
  1. **Upper Threshold Voltage ($V_{UTP}$):** The input voltage level at which the output switches when the input is increasing.
  2. **Lower Threshold Voltage ($V_{LTP}$):** The input voltage level at which the output switches when the input is decreasing.
* **Noise Immunity:** Any noise spikes smaller than the hysteresis width ($V_H$) cannot cause false triggering around the threshold point.

#### **Inverting Op-Amp Schmitt Trigger Equations**
Input $V_{in}$ is applied to the inverting terminal ($V_-$), and positive feedback via $R_1$ and $R_2$ (with $R_2$ connected to reference voltage $V_{\text{ref}}$ or Ground) is applied to the non-inverting terminal ($V_+$).

* **With $V_{\text{ref}} = 0\text{ V}$ (Grounded $R_2$):**
  $$V_{UTP} = +\left(\frac{R_2}{R_1 + R_2}\right) V_{\text{sat}}$$
  $$V_{LTP} = -\left(\frac{R_2}{R_1 + R_2}\right) V_{\text{sat}}$$
* **With External Reference Voltage ($V_{\text{ref}} \neq 0$):**
  $$V_{UTP} = \left(\frac{R_1}{R_1 + R_2}\right) V_{\text{ref}} + \left(\frac{R_2}{R_1 + R_2}\right) V_{\text{sat}}$$
  $$V_{LTP} = \left(\frac{R_1}{R_1 + R_2}\right) V_{\text{ref}} - \left(\frac{R_2}{R_1 + R_2}\right) V_{\text{sat}}$$
* **Hysteresis Voltage ($V_H$):**
  $$V_H = V_{UTP} - V_{LTP} = 2\left(\frac{R_2}{R_1 + R_2}\right) V_{\text{sat}}$$

---

### 5.2 The 555 Universal Timer IC

#### **Internal Block Architecture**
The 555 Timer IC derives its name from its internal voltage divider consisting of **three $5\text{ k}\Omega$ resistors** connected between $+V_{CC}$ and Ground.

```
              +Vcc (Pin 8)
                |
               [5k]
                |          |\
  Pin 5 (Ctrl)--+----------|-\  Upper Comparator (UC)
                | (2/3 Vcc)|  \________________________ R (Reset)
  Pin 6 (Thres)-|----------|+/                         |
                |          |/                     +----+----+
               [5k]                               |   SR    |---> Output Stage ---> Pin 3 (Out)
                |          |\                     |Flip-Flop|
  Pin 2 (Trig)--|----------|-\  Lower Comparator  +----+----+
                | (1/3 Vcc)|  \________________________|S (Set)
                +----------|+/                         |
                |          |/                          +--------> Base of Discharge BJT (Q1)
               [5k]                                               (Collector = Pin 7)
                |                                                 (Pin 4 = Master Reset)
               GND (Pin 1)
```

1. **Resistive Voltage Divider:** Creates two reference voltages: $\frac{2}{3} V_{CC}$ and $\frac{1}{3} V_{CC}$.
2. **Two Voltage Comparators:**
   * **Upper Comparator (UC):** Non-inverting input is **Threshold (Pin 6)**; inverting input is fixed at $\frac{2}{3} V_{CC}$ (**Control Voltage, Pin 5**). When $V_{\text{threshold}} > \frac{2}{3} V_{CC}$, UC outputs HIGH and resets ($R=1$) the flip-flop.
   * **Lower Comparator (LC):** Inverting input is **Trigger (Pin 2)**; non-inverting input is fixed at $\frac{1}{3} V_{CC}$. When $V_{\text{trigger}} < \frac{1}{3} V_{CC}$, LC outputs HIGH and sets ($S=1$) the flip-flop.
3. **SR Flip-Flop:** Controls the output stage and the internal discharge transistor.
   * When **Set ($Q=1, \bar{Q}=0$):** Timer Output (Pin 3) is **HIGH**, and Discharge Transistor $Q_1$ is **OFF** (open).
   * When **Reset ($Q=0, \bar{Q}=1$):** Timer Output (Pin 3) is **LOW**, and Discharge Transistor $Q_1$ is **ON** (saturated to ground).
4. **Discharge Transistor ($Q_1$):** Open-collector NPN transistor connected to **Pin 7 (Discharge)**, used to discharge the external timing capacitor.
5. **Reset (Pin 4):** Active-low master reset that overrides all other inputs and forces the output LOW when pulled below $0.4\text{ V}$.

---

#### **555 Timer Operating Modes**

##### **A. Monostable Mode (One-Shot)**
* **External Circuitry:** Resistor $R_A$ connected from $V_{CC}$ to Pin 6 & Pin 7 (shorted together), and capacitor $C$ from Pin 6/7 to Ground. Trigger pulse applied to Pin 2.
* **Operation:**
  1. Initially, $\bar{Q} = 1$, keeping transistor $Q_1$ ON and clamping capacitor $C$ at $0\text{ V}$ (Output is LOW).
  2. When Trigger (Pin 2) drops below $\frac{1}{3} V_{CC}$, LC sets the flip-flop ($\bar{Q}=0$, Output goes HIGH).
  3. $Q_1$ turns OFF, and $C$ charges toward $V_{CC}$ through $R_A$.
  4. When $V_C$ reaches $\frac{2}{3} V_{CC}$, UC resets the flip-flop ($\bar{Q}=1$, Output goes LOW), and $Q_1$ turns ON, rapidly discharging $C$ to $0\text{ V}$.
* **Pulse Width Formula:**
  $$T = 1.1 R_A C \quad (\text{exact: } R_A C \ln(3) \approx 1.0986 R_A C)$$

##### **B. Astable Mode (Free-Running Oscillator)**
* **External Circuitry:** $R_A$ between $V_{CC}$ and Pin 7; $R_B$ between Pin 7 and Pin 6/Pin 2 (Pins 6 and 2 are tied together); capacitor $C$ from Pin 2/6 to Ground.
* **Operation:**
  1. Capacitor $C$ charges from $\frac{1}{3} V_{CC}$ to $\frac{2}{3} V_{CC}$ through **$R_A + R_B$** while $Q_1$ is OFF (Output is HIGH).
  2. At $\frac{2}{3} V_{CC}$, UC resets the flip-flop (Output goes LOW, $Q_1$ turns ON).
  3. Capacitor $C$ discharges from $\frac{2}{3} V_{CC}$ down to $\frac{1}{3} V_{CC}$ through **$R_B$ only** into Pin 7.
  4. At $\frac{1}{3} V_{CC}$, LC sets the flip-flop, repeating the cycle.
* **Timing & Duty Cycle Equations:**
  * **Charging Time (Output HIGH):**
    $$T_{\text{HIGH}} = 0.693 (R_A + R_B) C$$
  * **Discharging Time (Output LOW):**
    $$T_{\text{LOW}} = 0.693 R_B C$$
  * **Total Period ($T$) & Frequency ($f$):**
    $$T = T_{\text{HIGH}} + T_{\text{LOW}} = 0.693 (R_A + 2 R_B) C$$
    $$f = \frac{1}{T} = \frac{1.44}{(R_A + 2 R_B) C}$$
  * **Duty Cycle ($D$):**
    $$D\% = \left( \frac{T_{\text{HIGH}}}{T} \right) \times 100\% = \left( \frac{R_A + R_B}{R_A + 2 R_B} \right) \times 100\%$$
    *(Note: In a standard 555 astable circuit, Duty Cycle is always $> 50\%$. To achieve $\le 50\%$ duty cycle, a diode is placed in parallel with $R_B$, bypassing $R_B$ during the charging phase).*

##### **C. 555 Timer as a Schmitt Trigger**
* Tie **Pin 2 (Trigger)** and **Pin 6 (Threshold)** together and connect the external input signal $V_{in}$ directly to this node.
* The output switches HIGH when $V_{in}$ falls below $V_{LTP} = \frac{1}{3} V_{CC}$ and switches LOW when $V_{in}$ rises above $V_{UTP} = \frac{2}{3} V_{CC}$.
* **Hysteresis Width:** $V_H = \frac{2}{3} V_{CC} - \frac{1}{3} V_{CC} = \frac{1}{3} V_{CC}$.

---

## 6. Sample Questions & Worked Problems

### Part A: Short-Answer & Conceptual Questions

1. **Why does a Class-B push-pull amplifier suffer from crossover distortion, and how is it overcome in a Class-AB configuration?**
   * *Answer Hint:* Discuss the $0.7\text{ V}$ base-emitter cut-in barrier where neither NPN nor PNP conducts around the zero-crossing of the input wave. Explain how diode biasing sets the Q-point slightly above cutoff in Class-AB to keep both transistors marginally conducting at zero input.
2. **Explain why $|A\beta|$ is practically designed to be slightly greater than $1$ in sinusoidal oscillators.**
   * *Answer Hint:* If $|A\beta|$ is exactly $1$, component aging or temperature drift could drop it to $0.99$, causing oscillations to die out. Setting $|A\beta| > 1$ allows thermal noise to build up exponentially at power-on until amplifier saturation or AGC circuitry reduces the average loop gain to unity.
3. **Why can a standard 555 Astable Multivibrator not produce a $50\%$ duty cycle square wave without circuit modification? How can you modify it to achieve a $50\%$ duty cycle?**
   * *Answer Hint:* Because $T_{\text{HIGH}} = 0.693(R_A + R_B)C$ is always greater than $T_{\text{LOW}} = 0.693 R_B C$ since $R_A > 0$ (making $R_A = 0$ would short Pin 7 directly to $+V_{CC}$ and burn out transistor $Q_1$). Placing a diode across $R_B$ with $R_A = R_B$ makes $T_{\text{HIGH}} = 0.693 R_A C$ and $T_{\text{LOW}} = 0.693 R_B C$, achieving $D = 50\%$.
4. **Why is a minimum of three $RC$ sections required in a phase-shift oscillator using a single inverting amplifier?**
   * *Answer Hint:* A single $RC$ section can provide a theoretical maximum phase shift of $< 90^\circ$ (approaching $90^\circ$ only at $f = 0$ or $\infty$ where output vanishes). Two $RC$ sections cannot reach $180^\circ$ at a finite frequency. Thus, at least three cascaded $RC$ sections are required to easily provide $60^\circ$ each ($180^\circ$ total) at a finite frequency.

---

### Part B: Analytical & Derivation Questions

1. **Derive the maximum collector efficiency of a Class-B push-pull power amplifier and show that $\eta_{\max} = 78.5\%$.**
   * *Outline of Derivation:*
     * DC supply current over a full cycle of two half-waves: $I_{DC} = \frac{2}{\pi} I_m$, so $P_{DC} = V_{CC} I_{DC} = \frac{2}{\pi} V_{CC} I_m$.
     * AC output power: $P_{ac} = \frac{V_m I_m}{2}$.
     * Efficiency: $\eta = \frac{P_{ac}}{P_{DC}} = \frac{\pi}{4} \left(\frac{V_m}{V_{CC}}\right)$.
     * Under maximum swing ($V_m = V_{CC}$), $\eta_{\max} = \frac{\pi}{4} \approx 0.7854$ or $78.54\%$.
2. **Draw the circuit diagram of an Op-Amp Wien Bridge Oscillator and derive the expression for the frequency of oscillation $f_o$ and the minimum required amplifier gain.**
3. **With the help of capacitor charging/discharging waveforms, derive the expression for the time period $T$ of an Op-Amp Astable Multivibrator.**

---

### Part C: Numerical Design Problems (With Solutions)

#### **Problem 1: Class-B Power Amplifier Metrics**
A Class-B push-pull amplifier operates from a dual power supply of $\pm V_{CC} = \pm 20\text{ V}$ and drives an $8\ \Omega$ speaker load. If the peak output voltage swing is $V_m = 16\text{ V}$, calculate: (a) AC output power $P_{ac}$, (b) DC input power $P_{DC}$, (c) Efficiency $\eta$, and (d) Power dissipated by each transistor.

* **Solution:**
  * Peak load current: $I_m = \frac{V_m}{R_L} = \frac{16\text{ V}}{8\ \Omega} = 2\text{ A}$
  * **(a) AC Output Power:**
    $$P_{ac} = \frac{V_m I_m}{2} = \frac{16 \times 2}{2} = 16\text{ W}$$
  * **(b) DC Input Power:**
    $$I_{DC} = \frac{2 I_m}{\pi} = \frac{2 \times 2}{\pi} \approx 1.273\text{ A}$$
    $$P_{DC} = V_{CC} \cdot I_{DC} = 20\text{ V} \times 1.273\text{ A} = 25.46\text{ W}$$
  * **(c) Efficiency ($\eta$):**
    $$\eta = \frac{P_{ac}}{P_{DC}} \times 100\% = \frac{16}{25.46} \times 100\% = 62.84\%$$
  * **(d) Power Dissipated per Transistor:**
    $$P_{d(\text{total})} = P_{DC} - P_{ac} = 25.46\text{ W} - 16\text{ W} = 9.46\text{ W}$$
    $$P_{d(\text{per BJT})} = \frac{9.46\text{ W}}{2} = 4.73\text{ W}$$

---

#### **Problem 2: RC Phase Shift Oscillator Design**
Design an Op-Amp RC Phase Shift Oscillator to oscillate at a frequency of $f_o = 1\text{ kHz}$. Choose a standard capacitor value of $C = 0.01\ \mu\text{F}$.

* **Solution:**
  1. **Find Feedback Resistor $R$:**
     $$f_o = \frac{1}{2\pi R C \sqrt{6}} \implies R = \frac{1}{2\pi \cdot (1 \times 10^3) \cdot (0.01 \times 10^{-6}) \cdot \sqrt{6}}$$
     $$R = \frac{1}{1.539 \times 10^{-4}} \approx 6.5\text{ k}\Omega$$
  2. **Select Op-Amp Gain Resistors ($R_1$ and $R_f$):**
     * To avoid loading the last $RC$ stage, choose the input resistor $R_1 = R = 6.5\text{ k}\Omega$ (or at least $10 R$ if separate).
     * From the Barkhausen gain requirement:
       $$\frac{R_f}{R_1} \ge 29 \implies R_f \ge 29 \times 6.5\text{ k}\Omega = 188.5\text{ k}\Omega$$
     * Choose $R_f = 200\text{ k}\Omega$ (or a $180\text{ k}\Omega$ fixed resistor in series with a $50\text{ k}\Omega$ potentiometer) to ensure reliable startup.

---

#### **Problem 3: Schmitt Trigger Threshold Calculation**
An inverting Op-Amp Schmitt Trigger has saturation voltages of $\pm V_{\text{sat}} = \pm 12\text{ V}$. The positive feedback network consists of $R_1 = 10\text{ k}\Omega$ (connected from output to $V_+$) and $R_2 = 2\text{ k}\Omega$ (connected from $V_+$ to a reference voltage $V_{\text{ref}} = 2\text{ V}$). Calculate $V_{UTP}$, $V_{LTP}$, and the hysteresis voltage $V_H$.

* **Solution:**
  * Using superposition at the non-inverting node $V_+$:
    $$V_+ = \left(\frac{R_1}{R_1 + R_2}\right) V_{\text{ref}} + \left(\frac{R_2}{R_1 + R_2}\right) V_o$$
    $$V_+ = \left(\frac{10}{10 + 2}\right)(2\text{ V}) + \left(\frac{2}{10 + 2}\right) V_o = 1.67\text{ V} + \frac{1}{6} V_o$$
  * **Upper Threshold ($V_o = +12\text{ V}$):**
    $$V_{UTP} = 1.67\text{ V} + \frac{1}{6}(12\text{ V}) = 1.67\text{ V} + 2\text{ V} = +3.67\text{ V}$$
  * **Lower Threshold ($V_o = -12\text{ V}$):**
    $$V_{LTP} = 1.67\text{ V} + \frac{1}{6}(-12\text{ V}) = 1.67\text{ V} - 2\text{ V} = -0.33\text{ V}$$
  * **Hysteresis Voltage ($V_H$):**
    $$V_H = V_{UTP} - V_{LTP} = 3.67 - (-0.33) = 4.0\text{ V}$$

---

#### **Problem 4: 555 Timer Astable Circuit Analysis**
A 555 Timer is configured as an astable multivibrator with $R_A = 4.7\text{ k}\Omega$, $R_B = 10\text{ k}\Omega$, and $C = 0.1\ \mu\text{F}$. Determine the charging time ($T_{\text{HIGH}}$), discharging time ($T_{\text{LOW}}$), oscillation frequency ($f$), and duty cycle ($D\%$).

* **Solution:**
  * **Charging Time ($T_{\text{HIGH}}$):**
    $$T_{\text{HIGH}} = 0.693 (R_A + R_B) C = 0.693 \times (4.7 + 10) \times 10^3 \times 0.1 \times 10^{-6} = 1.019\text{ ms}$$
  * **Discharging Time ($T_{\text{LOW}}$):**
    $$T_{\text{LOW}} = 0.693 R_B C = 0.693 \times 10 \times 10^3 \times 0.1 \times 10^{-6} = 0.693\text{ ms}$$
  * **Total Period & Frequency:**
    $$T = T_{\text{HIGH}} + T_{\text{LOW}} = 1.019\text{ ms} + 0.693\text{ ms} = 1.712\text{ ms}$$
    $$f = \frac{1}{T} = \frac{1}{1.712 \times 10^{-3}} \approx 584.1\text{ Hz}$$
  * **Duty Cycle ($D\%$):**
    $$D\% = \frac{T_{\text{HIGH}}}{T} \times 100\% = \frac{1.019}{1.712} \times 100\% = 59.5\%$$