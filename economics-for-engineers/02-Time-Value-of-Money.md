# 02 — Time Value of Money

> **Why this chapter comes first.** Every investment question — NPV, IRR, BCR, replacement, future
> worth — is built on discounting. If "a rupee today is worth more than a rupee tomorrow" is not
> automatic, the later chapters will feel like magic.

---

## Learning objectives

After studying this chapter you should be able to:
1. Compute simple and compound interest and explain when each applies.
2. Convert between nominal and effective interest rates, including continuous compounding.
3. Draw and interpret cash-flow diagrams.
4. Move money between time periods using present worth and future worth factors.
5. Handle annuities (ordinary and annuity-due) and use the six standard factors.
6. Explain why time value of money is important in engineering decisions.
7. Answer the PYQs on TVM, NPV meaning, and advantages/disadvantages of future worth.

---

## 1. Prerequisites and basic concepts

- A **rupee received today** can earn interest; a rupee received in one year cannot. Hence money
  received earlier is worth more.
- **Interest** is the price paid for the use of money over time.
- Two conventions: **simple interest** (interest always on the original principal) and **compound
  interest** (interest on principal + accumulated interest) — the latter is the standard in engineering
  economy.

---

## 2. Explanation from zero

### 2.1 Simple interest

$$I = P\,i\,n, \qquad A = P(1 + i n)$$

- $P$ = principal (Rs), $i$ = rate per period, $n$ = number of periods, $I$ = interest (Rs),
  $A$ = amount (Rs). Simple interest is used for short-term commercial loans, not for project
  evaluation.

### 2.2 Compound interest

Interest is added to the principal each period and earns interest in the next period:

$$A_n = P(1+i)^n, \qquad A = P + F \quad\text{(amount)}$$

**Derivation by induction.**
Year 0: $P$. Year 1: $P(1+i)$. Year 2: $P(1+i)(1+i) = P(1+i)^2$. In general after $n$ periods the
principal has been multiplied by $(1+i)$ exactly $n$ times, so $A = P(1+i)^n$.

### 2.3 Nominal, periodic and effective rates

- **Periodic rate** $i_m = i/m$ when a nominal annual rate $i$ is compounded $m$ times a year.
- **Effective annual rate (EAR)** — the true one-year growth rate:

$$i_{eff} = \left(1 + \frac{i}{m}\right)^{m} - 1$$

- **Continuous compounding** — the limit as $m \to \infty$:

$$i_{eff} = e^{i} - 1 \quad\text{(with $i$ as a decimal)}$$

Because $(1 + i/m)^m < e^{i}$, more frequent compounding gives a slightly higher effective rate, but the
difference is small for normal rates (e.g. 10% nominal: annual 10.00%, quarterly 10.38%, monthly
10.47%, continuous 10.52%).

### 2.4 Cash-flow diagrams

A cash-flow diagram puts money on a time axis.

```
        0        1        2        3
        |        |        |        |
        |--------+--------+--------+
   +100 |                              (receipt at t=0)
        |
        |↓ 200                    ↑ 150
        +-------------------------+---+---
                                   t=3
```

Rules: **arrows up = receipts (inflows)**; **arrows down = disbursements (outflows)**; time runs left to
right; the number on an arrow is the amount in Rs at that date. Always check units of time — a rate
"per annum" must be matched with periods in years.

> **PYQ** — 2022-2023 Group A item III asks exactly this: *"What do you mean by Cash-flow diagram?"*

### 2.5 Present worth and future worth

- **Present worth (PW, P)** — the value today of a future amount:
  $$P = F(1+i)^{-n}$$
- **Future worth (FW, F)** — the value at the end of $n$ periods of an amount today:
  $$F = P(1+i)^n$$

These two are **equivalents**: anything done in present worth can be done in future worth, and the
decision is unchanged (this is the basis of the future-worth PYQ).

### 2.6 Annuities

An **annuity** is a series of equal cash flows at equal time intervals.

- **Ordinary annuity** — payments at the **end** of each period (the usual case).
- **Anuity-due** — payments at the **beginning** of each period.

> **PYQ** — 2024-2025 Group A item V: *"A fixed cash flow in each year for a specified number of years
> is called as……."* → **an annuity**.

---

## 3. The six standard factors

Let $i$ = rate per period, $n$ = number of periods.

| Factor | Name | Formula | Meaning |
|---|---|---|---|
| $(P/F,i,n)$ | present worth of a future single amount | $\dfrac{1}{(1+i)^n}$ | What Rs 1 received in $n$ periods is worth today |
| $(F/P,i,n)$ | future worth of a present single amount | $(1+i)^n$ | What Rs 1 today grows to in $n$ periods |
| $(P/A,i,n)$ | present worth of an ordinary annuity | $\dfrac{(1+i)^n - 1}{i(1+i)^n} = \dfrac{1-(1+i)^{-n}}{i}$ | Present worth of Rs 1 per period for $n$ periods |
| $(F/A,i,n)$ | future worth of an ordinary annuity | $\dfrac{(1+i)^n - 1}{i}$ | Value at $n$ of Rs 1 per period |
| $(A/P,i,n)$ | capital recovery factor | $\dfrac{i(1+i)^n}{(1+i)^n - 1}$ | Constant payment that recovers $P$ in $n$ periods |
| $(A/F,i,n)$ | sinking fund factor | $\dfrac{i}{(1+i)^n - 1}$ | Constant deposit that accumulates to a future amount |

**Useful identities**

- $(P/F)\,(F/P) = 1$, $(P/A)\,(A/P) = 1$, $(F/A)\,(A/F) = 1$.
- $(F/A,i,n) = (P/A,i,n)(1+i)^n$.
- $F = P(A/P,i,n)$ and $P = F(A/F,i,n)$.
- Annuity-due factors: multiply the ordinary-annuity factor by $(1+i)$.

**Derivation of $(P/A,i,n)$** — sum of the present worths of Rs 1 at periods 1…n:

$$P = (1+i)^{-1} + (1+i)^{-2} + \cdots + (1+i)^{-n}$$

Multiply by $(1+i)$ and subtract the series from itself; the geometric series gives

$$P(1+i) - P = 1 - (1+i)^{-n} \;\Rightarrow\; P = \frac{1-(1+i)^{-n}}{i}$$

---

## 4. Formulas with variables and units

| Formula | Variables | Use |
|---|---|---|
| $A = P(1+i)^n$ | $A$ amount (Rs), $P$ principal (Rs), $i$ rate/period, $n$ periods | Growth of a single sum |
| $P = F(1+i)^{-n}$ | $F$ future amount (Rs) | Discounting a single sum |
| $i_{eff} = (1+i/m)^m - 1$ | $m$ compounding periods per year | Effective rate |
| $i_{eff} = e^i - 1$ | $e$ = 2.71828 | Continuous compounding |
| $P = A(P/A,i,n)$ | $A$ uniform annual amount (Rs/yr) | PW of an annuity |
| $F = A(F/A,i,n)$ | same | FW of an annuity |
| $P = F(A/F,i,n)$ | $F$ target amount (Rs) | Sinking fund to reach a target |
| $A = P(A/P,i,n)$ | $P$ present amount (Rs) | Capital recovery / EMI |
| $i_{real} = \dfrac{1+i_{nom}}{1+f} - 1$ | $f$ inflation rate | Real return ([Ch. 03](03-Inflation-and-CPI.md)) |

---

## 5. Worked examples

### 5.1 Example 1 — simple vs compound interest (Supplementary)

**Given:** Rs 1,00,000 at 10% p.a. for 5 years.
**Required:** amount under simple and compound interest.
**Formula:** Simple $A = P(1+in)$; Compound $A = P(1+i)^n$.
**Substitution:** Simple: $A = 1,00,000(1 + 0.10 \times 5) = 1,00,000 \times 1.5 = 1,50,000$.
Compound: $(1.1)^5 = 1.61051$; $A = 1,00,000 \times 1.61051 = 1,61,051$.
**Answer:** Simple = **Rs 1,50,000**; Compound = **Rs 1,61,051**; compound exceeds simple by
**Rs 11,051**.
**Reasonableness check:** the gap must be the interest earned on interest — with rates of 10% for 5
years, a gap of about 7% of principal is plausible.

### 5.2 Example 2 — effective rate with quarterly and continuous compounding

**Given:** nominal 10% p.a. compounded quarterly.
**Required:** effective annual rate; and the continuous-compounding equivalent.
**Formula:** $i_{eff} = (1 + i/m)^m - 1$; continuous $i_{eff} = e^{i} - 1$.
**Substitution:** Quarterly: $(1 + 0.10/4)^4 - 1 = (1.025)^4 - 1 = 1.103813 - 1 = 0.103813$.
Continuous: $e^{0.10} - 1 = 1.105171 - 1 = 0.105171$.
**Answer:** Quarterly effective rate = **10.38% p.a.**; continuous = **10.52% p.a.**
**Reasonableness check:** both lie between the nominal 10% and the monthly figure 10.47%; continuous is
the largest, as expected.
*(This is PYQ 2024-2025 Group A items I and VIII — printed twice in the same paper.)*

### 5.3 Example 3 — present worth of a mixed cash-flow stream (Supplementary)

**Given:** cash flows — Rs −50,000 at $t=0$, Rs +20,000 at $t=1$, Rs +25,000 at $t=2$, Rs +30,000 at
$t=3$; $i = 12\%$.
**Required:** net present value.
**Formula:** $NPV = \sum CF_t (1+i)^{-t}$.
**Substitution:**
- $t=0$: $-50,000 \times 1 = -50,000$
- $t=1$: $20,000 \times 0.8874 = 17,748$
- $t=2$: $25,000 \times 0.7872 = 19,680$
- $t=3$: $30,000 \times 0.7118 = 21,354$
$NPV = -50,000 + 17,748 + 19,680 + 21,354 = 8,782$.
**Answer:** **NPV ≈ +Rs 8,782** (positive → accept).
**Reasonableness check:** total undiscounted inflows Rs 75,000 exceed the outlay of Rs 50,000, so a
positive NPV at 12% is expected.

### 5.4 Example 4 — future worth of an annuity and a sinking fund (Supplementary)

**Given:** Rs 10,000 deposited at the end of each year for 8 years at 10% p.a.
**Required:** (a) future worth at the end of year 8; (b) the annual deposit needed to accumulate
Rs 5,00,000 at the end of year 8.
**Formula:** (a) $F = A(F/A,i,n)$; (b) $A = F(A/F,i,n)$.
**Substitution:** (a) $(F/A,10\%,8) = 11.4359$; $F = 10,000 \times 11.4359 = 1,14,359$.
(b) $(A/F,10\%,8) = 0.08744$; $A = 5,00,000 \times 0.08744 = 43,720$.
**Answer:** (a) **Rs 1,14,359**; (b) **Rs 43,720 per year**.
**Reasonableness check:** 8 deposits of Rs 43,720 (total Rs 3,49,760) growing to Rs 5,00,000 is
consistent with 10% compounding for 8 years.

### 5.5 Example 5 — capital recovery (equivalent annual cost)

**Given:** a machine costing Rs 4,00,000 with salvage Rs 40,000 after 6 years; operating cost
Rs 30,000 per year; $i = 12\%$.
**Required:** equivalent uniform annual cost.
**Formula:** $EUAC = (P - S)(A/P,i,n) + S\,i + \text{annual operating cost}$ (or use
$EUAC = P(A/P) - S(A/F) + \text{opex}$).
**Substitution:** $(A/P,12\%,6) = 0.24323$; $(A/F,12\%,6) = 0.04323$.
$EUAC = 4,00,000(0.24323) - 40,000(0.04323) + 30,000 = 97,292 - 1,729 + 30,000 = 1,25,563$.
**Answer:** **EUAC ≈ Rs 1,25,563 per year.**
**Reasonableness check:** an annual charge of about 31% of the machine cost plus Rs 30,000 opex is
reasonable for a 6-year asset at 12%.

---

## 6. Common mistakes and how to avoid them

| Mistake | Why wrong | Correction |
|---|---|---|
| Using a nominal rate as if it were effective | Understates the true cost of money | Convert with $(1+i/m)^m-1$ |
| Mixing annual and monthly periods | Nonsense PW factors | Keep $i$ per period and $n$ in the same time unit |
| Dividing by $(1+i)^n$ instead of multiplying | Wrong direction of discounting | Discounting = multiply by $(1+i)^{-n}$ |
| Taking cash flows as all positive | Ignores the initial outlay | Draw the diagram and sign the arrows |
| Treating an annuity-due as an ordinary annuity | Overstates/understates PW by one period | Multiply by $(1+i)$ |
| Using future worth factors as present worth factors | Wrong answer | $(P/A)$ < 1 always; $(F/A)$ > 1 always |

---

## 7. Likely one-mark questions with answers

| Question | Answer |
|---|---|
| What do you mean by Cash-flow diagram? (PYQ 2022-2023, A-III) | A time-scaled diagram of cash receipts (upward arrows) and disbursements (downward arrows) plotted against time |
| Time value of money theory describes money received in the current time which is more valuable than money received in future (T/F) (PYQ 2022-2023, A-VII) | **True** |
| If the nominal rate of interest is 10% per annum and there is quarterly compounding the effective rate will be: (PYQ 2024-2025, A-I & A-VIII) | **10.38% p.a.** |
| A fixed cash flow in each year for a specified number of years is called as… (PYQ 2024-2025, A-V) | **An annuity** |
| The concept that value of a rupee to be received in future is less than the value of a rupee on hand today is known as: (PYQ 2024-2025, A-IX) | **Time value of money** |
| The cash flows method utilized by IRR and NPV is known as ______ (PYQ 2022-2023, A-IV) | **Discounted cash-flow technique** |
| What is the difference between annually and continuously compounding interest? (Supplementary one-liner) | Annual compounding applies $(1+i)$ once a year; continuous compounding applies $e^{i}$ per year and always yields a slightly higher effective rate |
| Define compounding. (Supplementary) | Interest earned on the accumulated interest as well as the original principal |

---

## 8. Five-mark theory answers in exam-ready format

### Q. What is time value of money? Why is it important? (PYQ 2022-2023, C-Q8(a) [2] and C-Q8(d) [4])

**Definition (2 marks).** The time value of money is the principle that a sum of money available now
is worth more than the same sum available at some future date, because money available now can be
invested to earn a return. Equivalently, a future amount must be discounted to compare it with today's
money.

**Importance (4 marks).**
1. **Comparability** — without discounting, a Rs 1 lakh now and a Rs 1 lakh in 5 years look equal;
   discounting shows their true difference.
2. **Correct project selection** — NPV, IRR and BCR all require discounted cash flows; ignoring the time
   value systematically favours long projects.
3. **Cost of capital** — interest is the price of capital; converting future money into present money
   measures the true cost of a project against the return the firm could obtain elsewhere.
4. **Real purchasing power** — with inflation, money received later buys less; real interest rate
   $i' = (1+i)/(1+f) - 1$ captures this ([Chapter 03](03-Inflation-and-CPI.md)).

### Q. Difference between annually and continuously compounding interest. (PYQ 2022-2023, C-Q8(b) [4])

| Basis | Annual compounding | Continuous compounding |
|---|---|---|
| Compounding periods | $m = 1$ per year | $m \to \infty$ |
| Growth factor over 1 year | $(1+i)^1$ | $e^{i}$ |
| Effective rate | $(1+i)-1 = i$ | $e^{i}-1$ |
| Numerical (i = 10%) | 10.000% | 10.517% |
| Interpretation | Interest credited once a year | Interest credited continuously at the instantaneous rate |

**Conclusion:** continuous compounding gives a marginally higher effective rate because money is
"invested" for shorter sub-periods; the difference is small but always in the same direction.

### Q. What does net present value mean? (PYQ 2022-2023, C-Q8(c) [5])

1. **Definition:** NPV is the difference between the present worth of all cash inflows (benefits) and
   the present worth of all cash outflows (costs) of a project, taken at the decision maker's
   discount rate: $NPV = \sum CF_t (1+i)^{-t}$.
2. **Interpretation:** NPV is the maximum amount the firm could pay for the project at time zero and
   still break even — equivalently, the value the project adds to the firm at time zero.
3. **Decision rule:** NPV > 0 → accept; NPV = 0 → indifferent (the project earns exactly the required
   rate); NPV < 0 → reject.
4. **Mutually exclusive projects:** choose the one with the **larger** NPV, not the larger IRR.
5. **Strength:** it accounts for the time value of money, the scale of the project, and the timing of
   every cash flow, and it gives a direct money answer.
6. **Limitation:** it depends on the estimated cash flows and the chosen discount rate; when
   capital is rationed, use the profitability index or BCR.

### Q. Advantages and disadvantages of Future Worth. (PYQ 2022-2023, C-Q10(a) [8], (b) [7])

**Advantages (8)**
1. All alternatives are compared at one common future date, making the comparison consistent.
2. Particularly natural when the alternatives have **different lives** and a common study period is used
   (e.g. repeatability assumption), since future worth handles repeated cycles.
3. Matches the cash-flow reality of a project that delivers benefits mainly in later years.
4. Simple algebra: $F = P(1+i)^n$ and $F = A(F/A,i,n)$.
5. Handles non-uniform cash flows by shifting each amount forward to the common date.
6. Useful when the decision maker's real question is "how large will the project become?"
7. Can include reinvestment assumptions explicitly.
8. Equivalent to present worth, so the decision is identical.

**Disadvantages (7)**
1. Future amounts are larger and less intuitive to compare with today's rupees.
2. The answer depends heavily on the chosen future date; a distant date inflates all figures.
3. Reinvestment is implicitly assumed at the discount rate — future-worth analysis makes the
   reinvestment assumption explicit, which may be unrealistic.
4. For long horizons, rounding and the effect of large numbers reduce accuracy.
5. It cannot show directly how much money is created at time zero (NPV does).
6. Discounting far into the future requires long-range forecasts of inflation and rates.
7. If the analysis period is not fixed, future-worth comparisons can mislead.

---

## 9. Fifteen-mark answer structure where applicable

**Q. "Compare two alternatives using present worth and future worth."**

| Marks | Content |
|---|---|
| 3 | Draw cash-flow diagrams for both alternatives; state the discount rate and the study period |
| 4 | Present worth of each alternative (show factors used) |
| 4 | Future worth of each alternative (show factors used) |
| 2 | Comparison table: PW, FW, NPV of each; explain why PW and FW give the same ranking |
| 2 | Decision, assumptions stated, and sensitivity note |

---

## 10. PYQ references

| Year | Question | Concept |
|---|---|---|
| 2022-2023 | A-III | Cash-flow diagram |
| 2022-2023 | A-IV | DCF technique (IRR, NPV) |
| 2022-2023 | A-VII | TVM statement (True) |
| 2022-2023 | C-Q8(a)–(d) | TVM, annual vs continuous compounding, meaning of NPV, importance of TVM |
| 2022-2023 | C-Q10(a),(b) | Advantages and disadvantages of future worth |
| 2023-2024 | C-Q8(a) | Nominal rate, inflation and real rate $i'$ |
| 2024-2025 | A-I, A-VIII | Effective rate for 10% nominal with quarterly compounding |
| 2024-2025 | A-V | Annuity |
| 2024-2025 | A-IX | Time value of money concept |
| 2024-2025 | C-Q8 | IRR by interpolation ([Ch. 06](06-Investment-Appraisal-NPV-IRR-BCR.md)) |

---

## 11. Practice questions with answers and explanations

**Q1.** Find the PW of Rs 25,000 due in 4 years at 8% p.a. (Supplementary)
**A.** $P = 25,000 \times (1.08)^{-4} = 25,000 \times 0.73503 = 18,376$. **Answer Rs 18,376.**
*Check:* the present amount must be less than Rs 25,000 — correct.

**Q2.** A project costs Rs 1,00,000 now and returns Rs 40,000 per year for 4 years. Find the IRR
range. (Supplementary)
**A.** At 10%: PW of inflows $= 40,000 \times 3.1699 = 1,26,796$, NPV $= +26,796$.
At 20%: $40,000 \times 2.5887 = 1,03,548$, NPV $= +3,548$. At 22%: $40,000 \times 2.5059 = 1,00,236$,
NPV $= +236$; at 23%: $40,000 \times 2.4742 = 98,968$, NPV $= -1,032$.
**Answer:** IRR lies between 22% and 23% (about 22.2%). *Check:* NPV must cross zero as the rate rises.

**Q3.** What is the difference between an ordinary annuity and an annuity-due? Give the factor relation.
**A.** Ordinary annuity payments occur at the **end** of each period; annuity-due payments occur at the
**beginning**. Since every payment of an annuity-due is received one period earlier, it is worth more:
$P_{due} = P_{ordinary}(1+i)$ and $F_{due} = F_{ordinary}(1+i)$.

**Q4.** A machine saves Rs 40,000 per year for 6 years and has a salvage value of Rs 20,000 at the end
of year 6. If the required return is 15%, what is the maximum purchase price? (Supplementary)
**A.** PW of savings $= 40,000(P/A,15\%,6) = 40,000 \times 3.7845 = 1,51,380$; PW of salvage
$= 20,000(P/F,15\%,6) = 20,000 \times 0.4323 = 8,646$. Maximum price $= 1,51,380 + 8,646 = 1,60,026$.
**Answer: Rs 1,60,026.** *Check:* the price must exceed the undiscounted sum of savings
(Rs 2,40,000) only if... it must be **less** than Rs 2,60,000 — correct.

---

## 12. Chapter summary

- Money now > money later, because money now can earn interest.
- Simple interest is for short loans; compound interest is the engine of engineering economy.
- $i_{eff} = (1+i/m)^m - 1$ for periodic, $e^{i}-1$ for continuous compounding.
- Discounting = multiply by $(1+i)^{-n}$; the six factors cover single sums and annuities.
- Present worth and future worth are equivalent methods; the decision is the same.
- IRR/NPV/BCR ([Ch. 06](06-Investment-Appraisal-NPV-IRR-BCR.md)) are all applications of this chapter.

## 13. Revision checklist

- [ ] Can I write all six factor formulas from memory?
- [ ] Can I convert 10% nominal quarterly into an effective rate (10.38%)?
- [ ] Can I draw and label a cash-flow diagram?
- [ ] Do I know the difference between an annuity and an annuity-due?
- [ ] Can I give the 4 reasons why the time value of money matters (exam-ready)?
- [ ] Can I list 5 advantages and 5 disadvantages of future worth?

---

## Related notes

[01 Basics](01-Basics-and-Engineering-Economy.md) · [03 Inflation & CPI](03-Inflation-and-CPI.md) ·
[06 NPV/IRR/BCR](06-Investment-Appraisal-NPV-IRR-BCR.md) · [12 Short-Answer Bank](12-Short-Answer-Question-Bank.md) ·
[13 Numerical Practice](13-Numerical-Practice-Set.md) · [14 Formula Sheet](14-Formula-Sheet.md) ·
[15 Last-Minute Revision](15-Last-Minute-Revision.md)
