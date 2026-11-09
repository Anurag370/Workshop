# 06 — Investment Appraisal: NPV, IRR and BCR

> **Exam-critical chapter.** Investment appraisal appeared in all three years: BCR as a 15-mark
> four-part question (2022-2023) and a one-marker (2023-2024); IRR as a 15-mark numerical
> (2024-2025); NPV as a 5-mark part (2022-2023).

---

## Learning objectives

After studying this chapter you should be able to:
1. Explain the investment decision context and the role of the discount rate (MARR).
2. Compute NPV for a cash-flow stream and apply the decision rule.
3. Compute IRR, including by interpolation using the factor table supplied in the question.
4. Compute and interpret the BCR, and list its limitations.
5. Compare NPV, IRR and BCR and choose the right criterion for a given situation.
6. Solve the 2024-2025 IRR question and answer the 2022-2023 BCR question in exam-ready form.

---

## 1. Prerequisites

- Discounting, present worth factors and cash-flow diagrams from
  [Chapter 02](02-Time-Value-of-Money.md). If $P/F$, $P/A$ and $(1+i)^{-t}$ are not familiar, go back
  first.
- The discount rate is the **interest rate** used to convert future cash flows into today's money.

---

## 2. Explanation from zero

### 2.1 What an investment appraisal does

A firm has a limited budget and many possible projects. Each project has costs (now and later) and
benefits (later). Because the money spent today cannot also be spent later to earn interest, the
benefits and costs must be compared **at the same point in time** — today. Discounting does this.

### 2.2 The discount rate (MARR / cost of capital)

- **MARR (minimum acceptable rate of return)** — the lowest rate at which the firm is willing to accept
  a project; it reflects the return available on alternative investments and on borrowing.
- **Cost of capital** — the firm's marginal cost of funds (interest rate on borrowed capital, required
  return on equity).
- A project is worth doing only if it earns **at least** this rate.

### 2.3 Net present value (NPV)

$$
NPV = \sum_{t=0}^{n} \frac{CF_t}{(1+i)^t} \;=\; PW(\text{benefits}) - PW(\text{costs})
$$

**Interpretation.** NPV is the amount by which the project is worth more than it costs, measured at
time zero. It is also the maximum amount the firm could pay for the project (over and above the
already-identified costs) and still be no worse off.

**Decision rule.** NPV > 0 → accept; NPV = 0 → indifferent; NPV < 0 → reject. For mutually exclusive
projects, choose the **larger NPV**.

### 2.4 Internal rate of return (IRR)

The IRR is the discount rate at which NPV = 0 — the rate at which the project exactly earns its
required return.

**Decision rule.** IRR > MARR → accept; IRR = MARR → indifferent; IRR < MARR → reject.

**Computation by interpolation (as the paper requires)**

1. Find two rates $i_L$ and $i_H$ (usually from the supplied factor table) such that NPV is positive at
   $i_L$ and negative at $i_H$.
2. Interpolate:

$$
IRR = i_L + \frac{NPV_{i_L}}{NPV_{i_L} + |NPV_{i_H}|}\,(i_H - i_L)
$$

**Cautions.** (i) IRR assumes intermediate cash flows are reinvested at the IRR itself; (ii) a
non-conventional cash-flow pattern (sign changes more than once) can give several IRRs or none;
(iii) IRR is a *percentage*, so it cannot rank projects of different sizes.

### 2.5 Benefit–cost ratio (BCR)

$$
BCR = \frac{PW(\text{benefits})}{PW(\text{costs})}
$$

**Decision rule.** BCR > 1 → accept (benefits exceed costs in present-worth terms); BCR = 1 →
indifferent; BCR < 1 → reject. Note that BCR is equivalent to NPV > 0 when the denominator is the
same for all alternatives.

### 2.6 Other criteria (Supplementary, brief)

| Criterion | Formula | Comment |
|---|---|---|
| Payback period | Time until cumulative cash flow turns positive | Ignores time value and post-payback cash flows; useful for liquidity, not for value |
| Accounting rate of return | Average annual profit ÷ average investment | Simple; ignores time value |
| Profitability index | PW of net cash flows ÷ initial investment | Useful for capital rationing; ranks by value per rupee invested |

---

## 3. Important terminology

| Term | Definition |
|---|---|
| NPV | Present worth of cash inflows minus present worth of cash outflows |
| IRR | Rate at which NPV = 0 |
| BCR | Ratio of present worth of benefits to present worth of costs |
| MARR | Minimum acceptable rate of return (hurdle rate) |
| Discount factor | $1/(1+i)^t$; converts a future amount into today's money |
| Payback period | Time required to recover the initial investment from cash inflows |
| Mutually exclusive projects | Projects where only one can be chosen |
| Incremental analysis | Comparing alternatives by their differences |
| Reinvestment assumption | The rate at which intermediate cash flows are assumed to be reinvested |

---

## 4. Formulas, variables and units

| Formula | Variables | Use |
|---|---|---|
| $NPV = \sum CF_t(1+i)^{-t}$ | $CF_t$ cash flow at $t$ (Rs), $i$ discount rate | Accept/reject a project |
| $IRR$: $0 = \sum CF_t(1+IRR)^{-t}$ | — | Rate of return of a project |
| Interpolation: $IRR = i_L + \dfrac{NPV_L}{NPV_L - NPV_H}(i_H-i_L)$ | NPVs at two trial rates | When no table for IRR exists |
| $BCR = \dfrac{PW(\text{benefits})}{PW(\text{costs})}$ | both in Rs | Accept/reject; ranking under capital rationing |
| $PW(\text{benefits}) - PW(\text{costs})$ | Rs | NPV |
| $F/P = (1+i)^n$ etc. | | See [Ch. 02](02-Time-Value-of-Money.md) |

---

## 5. Worked examples

### 5.1 Example 1 — NPV (Supplementary)

**Given:** a machine costs Rs 5,00,000 now and saves Rs 1,80,000 per year for 5 years; salvage value
Rs 50,000 at the end of year 5; required return 12%.
**Required:** NPV and the decision.
**Formula:** $NPV = PW(\text{savings}) + PW(\text{salvage}) - PW(\text{cost})$.
**Substitution:** $(P/A,12\%,5) = 3.6048$; $(P/F,12\%,5) = 0.5674$.
$PW(\text{savings}) = 1,80,000 \times 3.6048 = 6,48,864$; $PW(\text{salvage}) = 50,000 \times 0.5674 =
28,370$; $NPV = 6,48,864 + 28,370 - 5,00,000 = 1,77,234$.
**Answer:** **NPV = +Rs 1,77,234 → accept.**
**Reasonableness check:** total undiscounted savings Rs 9,00,000 against a Rs 5,00,000 cost; a positive
NPV of about 35% of cost is plausible at 12%.

### 5.2 Example 2 — IRR by interpolation — the PYQ problem (2024-2025, C-Q8)

**Given:** initial outlay Rs 20,000; cash inflows Rs 5,000 (year 1), Rs 8,000 (year 2), Rs 10,000
(year 3), Rs 4,000 (year 4); present-value factors for Re 1 at 12%–16% supplied in the question.
**Required:** calculate the IRR.
**Formula:** NPV at a trial rate using the supplied factors; then linear interpolation between two
rates.
**Substitution:**
- At 13%: $5,000(0.885) + 8,000(0.783) + 10,000(0.693) + 4,000(0.613) - 20,000$
  $= 4,425 + 6,264 + 6,930 + 2,452 - 20,000 = 20,071 - 20,000 = \mathbf{+71}$.
- At 14%: $5,000(0.877) + 8,000(0.770) + 10,000(0.675) + 4,000(0.592) - 20,000$
  $= 4,385 + 6,160 + 6,750 + 2,368 - 20,000 = 19,663 - 20,000 = \mathbf{-337}$.
- (Check at 12%: $4,460 + 6,376 + 7,120 + 2,544 - 20,000 = +500$, so NPV falls as $i$ rises ✓.)
Interpolation:
$$IRR = 13\% + \frac{71}{71 + 337}\times (14\%-13\%) = 13\% + 0.1740\% = \mathbf{13.17\%}$$
**Answer:** **IRR ≈ 13.17% (about 13.2%).**
**Reasonableness check:** since the NPV is positive at 13% and negative at 14%, the IRR must lie
between them ✓; the interpolation is close to 13% because the NPV at 13% is small relative to the
rate interval.

### 5.3 Example 3 — BCR (Supplementary)

**Given:** a project costs Rs 4,00,000 now and Rs 50,000 at the end of year 2, and returns
Rs 1,50,000 at the end of each of years 1–4; discount rate 10%.
**Required:** BCR and the decision.
**Formula:** $BCR = PW(\text{benefits})/PW(\text{costs})$.
**Substitution:** $(P/A,10\%,4) = 3.1699$; $(P/F,10\%,2) = 0.8264$.
$PW(\text{benefits}) = 1,50,000 \times 3.1699 = 4,75,485$; $PW(\text{costs}) = 4,00,000 + 50,000
\times 0.8264 = 4,00,000 + 41,320 = 4,41,320$; $BCR = 4,75,485/4,41,320 = 1.0775$.
**Answer:** **BCR = 1.08 (> 1) → accept**; equivalently NPV = Rs 34,165 > 0.
**Reasonableness check:** BCR slightly above 1 means the project is worth slightly more than it costs.

### 5.4 Example 4 — comparing NPV and IRR (Supplementary)

**Given:** Project A: outlay Rs 1,00,000, returns Rs 1,20,000 in year 2. Project B: outlay Rs
2,00,000, returns Rs 2,60,000 in year 5. Required return 10%.
**Required:** which project should be chosen?
**Substitution:** A: $NPV = 1,20,000(1.1)^{-2} - 1,00,000 = 99,174 - 1,00,000 = -826$;
$IRR_A = (1,20,000/1,00,000)^{1/2} - 1 = 9.54\%$.
B: $NPV = 2,60,000(1.1)^{-5} - 2,00,000 = 1,61,350 - 2,00,000 = -38,650$;
$IRR_B = (2,60,000/2,00,000)^{1/5} - 1 = 5.39\%$.
**Answer:** both are unacceptable at 10% (negative NPV, IRR below the hurdle) — reject both. If both
were acceptable, NPV (money) would decide, not IRR.
**Reasonableness check:** both IRRs are below 10%, so rejection is consistent ✓.

---

## 6. Common mistakes and how to avoid them

| Mistake | Why wrong | Correction |
|---|---|---|
| Sign error: adding costs to NPV | NPV must be inflows − outflows | Keep the outlay negative |
| Interpolation with NPVs of the same sign | Invalid bracket | Choose $i_L$ with NPV > 0 and $i_H$ with NPV < 0 |
| Using $i_L$ and $i_H$ as percentages in a decimal formula | Arithmetic error | Convert to decimals consistently |
| Choosing the project with the higher IRR when NPVs disagree | IRR ignores scale | Choose the higher NPV |
| Treating BCR > 1 as "the project is 100% profitable" | BCR is a ratio of present worths | Say "benefits exceed costs by the ratio margin" |
| Ignoring salvage value or working capital | Wrong cash flows | Include all cash flows |
| Using the accounting rate of return in place of IRR | Ignores time value | IRR is a discounted measure |

---

## 7. Likely one-mark questions with answers

| Question | Answer |
|---|---|
| What Is the Benefit-Cost Ratio (BRC)? (PYQ 2023-2024, A-XII) | The ratio of the present worth of benefits to the present worth of costs; BCR > 1 means the project is economically acceptable |
| What does a Benefit-Cost-Ratio over 1.0 suggest? (PYQ 2022-2023, C-Q7(c)) | The present worth of benefits exceeds the present worth of costs, so the project earns more than the required return and should be accepted |
| The cash flows method utilized by IRR and NPV is known as ______ (PYQ 2022-2023, A-IV) | Discounted cash-flow technique |
| What does net present value mean? (PYQ 2022-2023, C-Q8(c)) | The difference between the present worth of benefits and the present worth of costs |
| Define MARR. (Supplementary) | Minimum acceptable rate of return — the hurdle rate below which a project is rejected |
| What is the IRR? (Supplementary) | The discount rate at which NPV = 0 |
| State the IRR decision rule. (Supplementary) | Accept if IRR ≥ MARR; reject if IRR < MARR |

---

## 8. Five-mark theory answers in exam-ready format

### Q. What is the Benefit-Cost Ratio, what is it used for, what does a value over 1.0 suggest, and what are its limitations? (PYQ 2022-2023, C-Q7: 6 + 1 + 2 + 6)

**(a) Definition [6].**
1. BCR is a **benefit–cost ratio**: the present worth of all benefits of a project divided by the present
   worth of all costs of the same project.
2. $BCR = PW(\text{benefits})/PW(\text{costs})$, with both numerator and denominator expressed at the
   same point in time (usually time zero) using the project's discount rate.
3. Costs include initial investment, operating and maintenance costs, taxes and negative salvage
   values; benefits include revenues, savings, salvage value and any other inflows.
4. It is a **dimensionless ratio**, so it can be compared across projects of different sizes.
5. Because it is computed from discounted cash flows, it respects the time value of money.
6. Example: PW of benefits Rs 4,75,485 and PW of costs Rs 4,41,320 → BCR = 1.08.

**(b) Use [1].** To screen and rank alternative investments, especially when capital is rationed and
when projects differ in size.

**(c) BCR over 1.0 [2].** It means the present worth of benefits exceeds the present worth of costs;
the project therefore earns more than the required rate of return and is **acceptable**. A BCR of 1.0
means exactly break-even at the discount rate.

**(d) Limitations [6].**
1. **Ranking problem** — for mutually exclusive projects, ranking by BCR can differ from ranking by NPV;
   the project with the highest BCR is not always the best.
2. **Scale insensitivity** — a small project with a high BCR may add less total value than a large
   project with a slightly lower BCR.
3. **Discount-rate sensitivity** — like NPV, it changes with the chosen discount rate.
4. **Subjectivity of classification** — what is put in "benefits" and what in "costs" (e.g. taxes,
   working capital) affects the ratio.
5. **Ignores the scale of investment and the timing pattern within the ratio** — useful for screening
   only.
6. **Data dependence** — errors in estimated benefits and costs pass directly into the ratio; it also
   says nothing about the probability of the outcomes.

### Q. Why is the time value of money important? (PYQ 2022-2023, C-Q8(d) [4])

1. **Money has time value** — a rupee today can be invested; the same rupee later cannot earn anything.
2. **Comparability** — cash flows occur at different times; discounting converts them to a common
   basis, so comparisons are valid.
3. **Correct investment decisions** — NPV, IRR and BCR depend on discounting; ignoring it systematically
   overvalues long-term projects.
4. **Cost of capital and inflation** — discounting at a rate that includes inflation (and using real
   cash flows with a real rate) reflects the true economic cost of funds.

### Q. What does net present value mean? (PYQ 2022-2023, C-Q8(c) [5])

See [Chapter 02](02-Time-Value-of-Money.md), Section 8 — the full model answer is given there and
should be reproduced here: definition, formula, interpretation, decision rule, use for mutually
exclusive projects, and one limitation.

---

## 9. Fifteen-mark answer structure where applicable

**Q. "IRR from cash flows"** (PYQ 2024-2025, C-Q8) — the answer should contain:

| Marks | Content |
|---|---|
| 2 | State the formula $0 = \sum CF_t(1+IRR)^{-t}$ and the cash-flow diagram |
| 4 | NPV at the lower trial rate with the supplied factors |
| 4 | NPV at the higher trial rate with the supplied factors |
| 3 | Interpolation formula and substitution |
| 2 | Answer with units and a note that the project is acceptable if IRR > MARR |

**Q. "Evaluate a project and recommend."** (Supplementary structure)

| Marks | Content |
|---|---|
| 3 | Cash-flow estimation (investment, operating costs, revenues, life, salvage, taxes) |
| 3 | Discount rate justification (MARR, cost of capital, risk) |
| 3 | NPV computation with factors |
| 2 | IRR computation (or BCR) |
| 2 | Comparison with alternatives, sensitivity/risk note |
| 2 | Recommendation with justification and monitoring plan |

---

## 10. PYQ references

| Year | Question | Concept |
|---|---|---|
| 2022-2023 | A-IV | DCF technique |
| 2022-2023 | C-Q7(a)–(d) | BCR definition, use, meaning of BCR > 1, limitations |
| 2022-2023 | C-Q8(c),(d) | Meaning of NPV; importance of TVM |
| 2023-2024 | A-XII | What is BCR |
| 2024-2025 | C-Q8 | IRR by interpolation with supplied factors |

---

## 11. Practice questions with answers and explanations

**Q1.** A project costs Rs 2,00,000 and returns Rs 60,000 at the end of years 1 and 2. Find NPV at 15%
and IRR. (Supplementary)
**A.** $NPV = 60,000(0.8696 + 0.7561) - 2,00,000 = 60,000(1.6257) - 2,00,000 = 97,542 - 2,00,000 =
-1,02,458$ (reject). IRR: $1 + i$ solves $(1+i)^{-1} + (1+i)^{-2} = 3.3333$; try 10%: 0.9091 + 0.8264 =
1.7355; try 0%: 1 + 1 = 2; as $i$ falls the sum rises — 10% gives 1.7355 which is less than 3.3333,
so no positive IRR exists (the total undiscounted return of Rs 1,20,000 is less than the cost).
**Answer:** NPV = −Rs 1,02,458; the project has **no positive IRR** — reject.
*Check:* undiscounted inflows Rs 1,20,000 < outlay Rs 2,00,000, so NPV must be negative ✓.

**Q2.** Under capital rationing, three projects have (NPV, investment) of (Rs 40,000, Rs 1,00,000),
(Rs 90,000, Rs 3,00,000) and (Rs 60,000, Rs 2,00,000). Which should be picked if only Rs 3,00,000 is
available? (Supplementary)
**A.** Profitability index: A = 0.40; B = 0.30; C = 0.30. Ranking by index gives A first, but by NPV
B is best and all three together need Rs 6,00,000. Choose B + C (Rs 5,00,000 — too much) or B + A
(Rs 4,00,000 — too much) → only one project fits: pick the one with the highest NPV that fits, i.e.
**B (NPV Rs 90,000)**.
**Answer:** B. *Check:* with a single-slot budget the index ranking is not decisive; NPV per rupee is
only a guide for multi-project selection.

**Q3.** Why can a project have a positive NPV but a lower IRR than an alternative? (Supplementary)
**A.** Because NPV measures total value added (absolute rupees) while IRR measures a percentage return
and ignores the scale of the investment. A small project can have a high IRR and a small NPV while a
large project has a lower IRR but a larger NPV; if capital is not rationed, choose the larger NPV.

---

## 12. Chapter summary

- Discount everything to time zero at the MARR, then compare benefits and costs.
- NPV = PW(benefits) − PW(costs); accept if > 0; choose the largest NPV among alternatives.
- IRR is the rate making NPV zero; find it by interpolation between a +NPV rate and a −NPV rate;
  the PYQ answer is **13.17%**.
- BCR = PW(benefits)/PW(costs); accept if > 1; useful under capital rationing but can mis-rank.

## 13. Revision checklist

- [ ] Can I write all three decision rules from memory?
- [ ] Can I do the IRR interpolation with the paper's factor table (13.17%)?
- [ ] Can I write the BCR answer in four parts (6+1+2+6)?
- [ ] Can I explain the NPV-vs-IRR ranking conflict?
- [ ] Do I know the limitations of BCR (at least four)?

---

## Related notes

[02 Time Value of Money](02-Time-Value-of-Money.md) · [03 Inflation & CPI](03-Inflation-and-CPI.md) ·
[07 Cost Estimation](07-Cost-Estimation-and-Learning-Curve.md) · [10 Decision Making](10-Engineering-Decision-Making.md) ·
[12 Short-Answer Bank](12-Short-Answer-Question-Bank.md) · [13 Numerical Practice](13-Numerical-Practice-Set.md) ·
[14 Formula Sheet](14-Formula-Sheet.md) · [15 Last-Minute Revision](15-Last-Minute-Revision.md)
