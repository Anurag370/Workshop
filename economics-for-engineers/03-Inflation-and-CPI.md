# 03 — Inflation and CPI

> **Exam-critical chapter.** The pair of questions *"How is CPI used to measure inflation?"* [5] and
> *"Does an increase in CPI mean inflation?"* [2] appeared **verbatim in two consecutive years**
> (2022-2023 C-Q11 and 2023-2024 C-Q11). Inflation-related one-markers appeared in all three years.

---

## Learning objectives

After studying this chapter you should be able to:
1. Define inflation and distinguish it from a one-time price change.
2. Construct and compute a CPI, and compute the inflation rate between two periods.
3. Explain WPI and how it differs from CPI.
4. Explain demand-pull, cost-push and built-in inflation, and stagflation.
5. Compute real and nominal interest rates and explain the Fisher relation.
6. Answer the exact-repeat PYQs and the inflation one-markers from all three years.

---

## 1. Prerequisites and basic concepts

- **Price level** — the overall level of prices in the economy.
- **Inflation** — a sustained, general rise in the price level. "General" is important: a rise in one
  commodity is not inflation.
- **Deflation** — a sustained fall in the general price level.
- **Purchasing power** — what one unit of money can buy; it falls when the price level rises.

---

## 2. Explanation from zero

### 2.1 The Consumer Price Index (CPI)

The CPI measures the **cost of living** of a typical urban consumer by tracking the price of a fixed
**market basket** of goods and services that families buy.

**Formula**

$$CPI_t = \frac{\text{Cost of the market basket at time } t}{\text{Cost of the market basket at base time}} \times 100$$

**Anatomy of the index**
- **Base period** — the reference year; its basket cost is the denominator (e.g. 2012 = 100).
- **Market basket** — the fixed list of goods and services (rice, wheat, milk, rent, transport, …).
- **Weights** — the importance of each item in the basket, taken from family expenditure surveys.
- **Collection** — prices are gathered in many cities and shops and averaged.

**CPI measures prices, not inflation.** Inflation is the **rate of change** of the CPI.

### 2.2 Inflation rate between two periods

$$f_{t-1 \to t} = \frac{CPI_t - CPI_{t-1}}{CPI_{t-1}} \times 100$$

Note the denominator: it is the **old** CPI (base-year convention), not the new one.

### 2.3 WPI versus CPI

| Basis | CPI | WPI |
|---|---|---|
| What it measures | Retail consumer prices | Wholesale/bulk prices of raw materials and finished goods |
| Basket | Consumer goods and services | Primary articles, fuel, power, manufactured goods |
| User | Household budgeting, wage/indexation | Cost of production, terms of trade |
| Level | Includes final-stage margins and taxes | Excludes retail margin and sales tax |

Both indices are published with a base year; both are used to compute inflation rates for their own
basket.

### 2.4 Types of inflation

| Type | Cause | Typical example |
|---|---|---|
| **Demand-pull** | Aggregate demand grows faster than the economy's capacity to supply ("too much money chasing too few goods") | Rapid growth in money supply during a boom |
| **Cost-push** | Input (factor) prices rise — wages, raw materials, energy — and are passed on | Oil price shock raising transport and fertiliser costs |
| **Built-in (cost-induced)** | Wages and prices are indexed so they rise automatically as the price level rises | Wage–price spiral |
| **Stagflation** | Stagnant output and high unemployment **combined with** inflation | Oil shock in the 1970s |

### 2.5 Effects of inflation

1. **Redistribution of income between creditors and debtors** — a fixed Rs 1,000 loan repaid next year
   buys less than it did, so borrowers gain and lenders lose; fixed incomes (salary, pension,
   rent) lose purchasing power while holders of assets (property, shares) gain.
2. **Erosion of savings** — the real return on deposits falls.
3. **Uncertainty and misallocation** — long-term contracts and investments become risky.
4. **Inflation tax** — the hidden loss on money held as cash.
5. **Menu and psychological costs** — firms must change prices, catalogues and quotes.
6. **Effect on engineering decisions** — a project's *nominal* cash flows must be deflated to real terms
   before discounting at a real rate, or the discount rate must include inflation.

### 2.6 Nominal vs real interest rates

- **Nominal rate $i$** — the rate actually quoted; contains compensation for inflation.
- **Real rate $i'$** — the return after removing the effect of inflation; it measures purchasing-power
  gain.

**Fisher relation**

$$(1+i) = (1+i')(1+f) \;\Rightarrow\; i' = \frac{1+i}{1+f} - 1$$

**Derivation:** 1 rupee invested at the nominal rate grows to $(1+i)$ rupees after a year; those rupees
buy only $(1+i)/(1+f)$ rupees' worth of goods because prices rose by factor $(1+f)$. The quotient is
the growth in purchasing power, which is $(1+i')$.

### 2.7 Hyperinflation and indexing

- **Hyperinflation** — extremely rapid inflation (e.g. 50%+ per month), which destroys savings and makes
  cash unusable; seen historically in Weimar Germany, Zimbabwe, and in high-inflation episodes in
  Argentina and Turkey.
- **Indexation** — linking wages, pensions, debt contracts or instalments to a price index so that real
  values are preserved.
- **Real cash-flow analysis** — convert nominal cash flows with $CF_{real} = CF_{nominal}/(1+f)^t$ and
  discount at the real rate, or discount nominal cash flows at $i_{nominal}$.

---

## 3. Important terminology

| Term | Definition |
|---|---|
| Inflation | A sustained rise in the general price level (fall in purchasing power) |
| CPI | Consumer Price Index — cost of a fixed basket of consumer goods relative to a base period |
| WPI | Wholesale Price Index — prices of goods traded in bulk |
| Base period | The reference period whose basket cost equals 100 |
| Market basket | The fixed set of goods and services used to compute the index |
| Weight | The importance (usually expenditure share) given to an item in the basket |
| Deflation | Sustained fall of the general price level |
| Stagflation | Stagnation + inflation occurring together |
| Real interest rate | Interest rate adjusted for inflation |
| Indexation | Linking payments to a price index to protect real value |

---

## 4. Formulas, variables and units

| Formula | Variables | Use |
|---|---|---|
| $CPI_t = \dfrac{C_t}{C_b}\times 100$ | $C_t$ = basket cost now (Rs), $C_b$ = basket cost in base period (Rs) | Build the index |
| $f = \dfrac{CPI_t - CPI_{t-1}}{CPI_{t-1}}\times 100$ | $f$ = inflation rate (% per period) | Rate of inflation between two periods |
| $i' = \dfrac{1+i}{1+f} - 1$ | $i$ nominal rate, $f$ inflation rate | Real return |
| $i = (1+i')(1+f) - 1$ | same | Nominal rate from a real rate |
| $CF_{real,t} = \dfrac{CF_{nom,t}}{(1+f)^t}$ | $f$ inflation rate per period | Deflate a cash-flow series |
| $Real\ value = \dfrac{Nominal\ value}{CPI/100}$ | CPI index | Convert between nominal and real |

---

## 5. Worked examples

### 5.1 Example 1 — building a CPI and the inflation rate (Supplementary)

**Given:** a family spends on four items. Quantity and prices:

| Item | Qty | Price year 1 (Rs) | Price year 2 (Rs) |
|---|---|---|---|
| Rice (kg) | 10 | 40 | 48 |
| Milk (litre) | 20 | 25 | 30 |
| Rice+Milk+Veg | — | — | — |
| Vegetables (kg) | 5 | 30 | 33 |
| Rent (month) | 1 | 6,000 | 6,600 |

**Required:** CPI for year 2 with year 1 as base, and the inflation rate.
**Formula:** basket cost = Σ (quantity × price); $CPI = (C_2/C_1)\times 100$.
**Substitution:**
Year 1 basket: $10(40) + 20(25) + 5(30) + 1(6,000) = 400 + 500 + 150 + 6,000 = 7,050$.
Year 2 basket: $10(48) + 20(30) + 5(33) + 1(6,600) = 480 + 600 + 165 + 6,600 = 7,845$.
$CPI_2 = (7,845/7,050)\times 100 = 111.28$.
Inflation $= (111.28 - 100)/100 \times 100 = 11.28\%$.
**Answer:** **CPI (year 1 = 100) = 111.28; inflation rate = 11.28% per year.**
**Reasonableness check:** every price rose, and the index rose by less than 12% because rent (the
heaviest weight) rose 10% while milk rose 20%.

### 5.2 Example 2 — real interest rate (PYQ 2023-2024, C-Q8(a))

**Given:** bank rate 5.5% compounded annually for one year; inflation 2% p.a. and then 8% p.a.
**Required:** identify $i$, $f$ and $i'$; compute $i'$ in both cases.
**Formula:** $i' = \dfrac{1+i}{1+f} - 1$.
**Substitution:** $i = 0.055$.
- $f = 0.02$: $i' = 1.055/1.02 - 1 = 1.034314 - 1 = 0.034314 \Rightarrow 3.43\%$.
- $f = 0.08$: $i' = 1.055/1.08 - 1 = 0.976852 - 1 = -0.023148 \Rightarrow -2.31\%$.
**Answer:** $i = 5.5\%$ (nominal), $f = 2\%$ then $8\%$ (expected inflation), $i' = \mathbf{+3.43\%}$
then **−2.31%**.
**Reasonableness check:** the real rate must be below the nominal rate, and with 8% inflation a 5.5%
nominal deposit must lose purchasing power — the negative result is correct.

### 5.3 Example 3 — deflating a cash flow (Supplementary)

**Given:** a project returns Rs 1,10,000 in year 2 with inflation 6% p.a. Discount rate 5% nominal.
**Required:** value in today's rupees and the correct rate to use.
**Formula:** $CF_{real} = CF_{nom}/(1+f)^t$; real discount rate $i' = (1+i)/(1+f)-1$.
**Substitution:** $CF_{real} = 1,10,000/(1.06)^2 = 1,10,000/1.1236 = 97,899$.
$i' = 1.05/1.06 - 1 = -0.009434$ (about −0.94%).
**Answer:** real cash flow **Rs 97,899**; discount it at the real rate, or equivalently discount the
nominal Rs 1,10,000 at 5% ($= 99,443$ would be wrong — it mixes nominal flow with the wrong rate).
**Reasonableness check:** deflating reduces the later amount, as expected.

---

## 6. Common mistakes and how to avoid them

| Mistake | Why wrong | Correction |
|---|---|---|
| Saying "an increase in CPI *is* inflation" | CPI is a *level*; inflation is its *rate of change* | The answer to PYQ (b) is **No** — an increase in CPI means the price level rose; inflation is the percentage rate of that rise |
| Using the new CPI as the denominator in the inflation formula | Reverses the ratio | Use $CPI_{t-1}$ in the denominator |
| Dividing nominal cash flows by a nominal rate and calling the result real | Mixes real and nominal | Deflate the flows and use the real rate, or keep nominal flows and nominal rate |
| Treating a single price rise (e.g. petrol) as inflation | Inflation is general and sustained | Name the basket and the base period |
| Writing the real rate as $i - f$ | Approximation only | Exact: $(1+i)/(1+f)-1$ |
| Confusing WPI with CPI | Different baskets and users | State "wholesale vs retail" |

---

## 7. Likely one-mark questions with answers

| Question | Answer |
|---|---|
| What is Inflation? (PYQ 2022-2023, A-V) | A sustained rise in the general price level, i.e. a fall in the purchasing power of money |
| How does inflation help in the redistribution of income? (PYQ 2022-2023, A-I) | It transfers purchasing power from fixed-income earners (savers, lenders, pensioners) to borrowers and owners of assets, since money repaid later is worth less |
| The combination of stagnation and inflation is known as ________. (PYQ 2023-2024, A-I) | **Stagflation** |
| What is WPI? (PYQ 2023-2024, A-III) | Wholesale Price Index — an index of prices of goods bought and sold in bulk at wholesale level |
| If too much money is chasing too few goods, the resulting inflation is known as ________. (PYQ 2024-2025, A-II) | **Demand-pull inflation** |
| High inflation levels in the economy lead to _______ in the supply of money. (PYQ 2024-2025, A-IV) | A **decrease / contraction** in the supply of money |
| When inflation is a result of an increase in the price of factors of production, the result is ________. (PYQ 2024-2025, A-XI) | **Cost-push inflation** |
| Does an increase in CPI mean inflation? (PYQ 2022-2023 & 2023-2024, C-Q11(b)) | **No.** An increase in CPI means the price level rose; inflation is the *rate* of that rise |
| Define stagflation. (PYQ 2023-2024, A-I) | Stagnant output/high unemployment occurring together with inflation |
| What is the base period in a CPI? (Supplementary) | The reference year whose basket cost is set equal to 100 |
| Define real interest rate. (Supplementary) | The rate adjusted for inflation, $i' = (1+i)/(1+f)-1$; the true growth in purchasing power |

---

## 8. Five-mark theory answers in exam-ready format

### Q. (a) How is CPI used to measure inflation? [5] — PYQ 2022-2023 C-Q11(a) and 2023-2024 C-Q11(a)

1. **Construction.** The CPI is built on a fixed *market basket* of goods and services purchased by a
   typical urban consumer, with weights taken from household expenditure surveys; prices are collected
   across cities and averaged; a base period is fixed with index = 100.
2. **Formula.** $CPI_t = (\text{cost of basket now}/\text{cost of basket in base period})\times 100$.
3. **From index to inflation.** The CPI measures the *level* of prices; the **rate of inflation** is
   obtained from two consecutive index values:
   $f = (CPI_t - CPI_{t-1})/CPI_{t-1} \times 100$.
4. **Use.** It is the official measure of consumer price inflation and is used for indexation of
   wages, pensions, rents and contracts, and for tracking the cost of living.
5. **Limitations (add for completeness).** Substitution bias (consumers switch to cheaper items),
   unmeasured quality changes, and the lag in data collection; for general price trends, WPI is used
   as a complementary index.

### Q. (b) Does an increase in CPI mean inflation? [2] — PYQ 2022-2023 C-Q11(b) and 2023-2024 C-Q11(b)

**Answer: No — not exactly.** An increase in CPI means that the **price level** has risen (buying the
same basket now costs more). *Inflation* is the **rate of increase** of the price level, computed as
the percentage change between two CPI values. Hence a rising CPI is the *measure* of inflation, and
inflation is defined as the rate at which the CPI rises; the CPI itself is an index number, not a rate.

### Q. State the different causes of Inflation. [5] — PYQ 2024-2025 B-Q3

1. **Demand-pull inflation** — aggregate demand grows faster than productive capacity; too much money
   chases too few goods.
2. **Cost-push inflation** — rising input prices (raw materials, energy, wages) are passed on to
   buyers.
3. **Built-in / cost-induced inflation** — wages and prices are indexed to the price level, creating a
   wage–price spiral.
4. **Monetary and fiscal factors** — excessive money and credit creation (loose monetary policy) and
   large government budget deficits financed by printing money.
5. **External and structural factors** — international price shocks (oil, food), devaluation of the
   currency, and supply bottlenecks (harvest failure, logistics disruption).
6. **Demand-side expectations and psychology** — anticipatory buying when inflation is expected.
7. **Conclusion:** inflation is a monetary symptom of several real causes, so controlling it needs both
   monetary restraint and supply-side remedies.

### Q. What is CPI or retail inflation? [9] — PYQ 2023-2024 C-Q8(b)

Write in this order: (1) definition of retail inflation; (2) construction of the index — basket,
weights, base period, price collection; (3) formula; (4) how inflation is derived from two CPI values
with formula; (5) worked mini-example of a basket cost rising from Rs 3,000 to Rs 3,150 → CPI 100 to
105, inflation 5%; (6) uses — cost of living, indexation of wages/rents, policy; (7) limitations;
(8) CPI vs WPI; (9) concluding statement that CPI is the standard retail price measure and that an
increase in the CPI indicates a rise in the price level.

### Q. Differentiate between CPI and WPI. [5] — Supplementary

| Basis | CPI | WPI |
|---|---|---|
| Level of market | Retail | Wholesale |
| Basket | Consumer goods and services | Raw materials, fuel, manufactured goods |
| Includes retail margin and indirect taxes | Yes | No |
| Representative of | Household cost of living | Cost of production / terms of trade |
| Typical user | Households, wage indexation | Producers, national accounts |

---

## 9. Fifteen-mark answer structure where applicable

**Q. "Inflation and engineering decision making."** (Supplementary structure)

| Marks | Content |
|---|---|
| 2 | Definition of inflation; CPI construction and formula |
| 2 | Types: demand-pull, cost-push, built-in, stagflation with one example each |
| 2 | Effects: redistribution of income, uncertainty, erosion of savings, inflation tax |
| 3 | Nominal vs real quantities; Fisher relation with derivation; deflating cash flows |
| 2 | Numerical: real interest rate calculation (5.5%, 2% and 8%) |
| 2 | Impact on engineering economy: cost escalation in estimates, MARR selection, contracts and escalation clauses |
| 1 | Limitations of CPI and conclusion |

---

## 10. PYQ references

| Year | Question | Concept |
|---|---|---|
| 2022-2023 | A-I, A-V | Inflation and redistribution of income; definition of inflation |
| 2022-2023 | C-Q11(a,b) | CPI used to measure inflation; increase in CPI vs inflation (**exact repeat**) |
| 2023-2024 | A-I, A-III | Stagflation; WPI |
| 2023-2024 | C-Q8(a) | Nominal rate, inflation, real rate (golfer) |
| 2023-2024 | C-Q8(b) | CPI / retail inflation |
| 2023-2024 | C-Q11(a,b) | CPI used to measure inflation; increase in CPI vs inflation (**exact repeat**) |
| 2024-2025 | A-II, A-IV, A-XI | Demand-pull; money supply; cost-push |
| 2024-2025 | B-Q3 | Causes of inflation |

---

## 11. Practice questions with answers and explanations

**Q1.** The CPI is 105.3 in year 1 and 112.8 in year 2. Find the inflation rate. (Supplementary)
**A.** $f = (112.8 - 105.3)/105.3 \times 100 = 7.5/105.3 \times 100 = 7.12\%$.
**Answer 7.12%.** *Check:* dividing by the old index gives a smaller rate than dividing by the new one.

**Q2.** A nominal return is 9% while inflation is 4%. Find the real return. (Supplementary)
**A.** $i' = 1.09/1.04 - 1 = 0.048077 \Rightarrow 4.81\%$.
**Answer 4.81%** (the approximation $9-4=5\%$ is close but not exact).

**Q3.** A loan of Rs 1,00,000 is repaid in 3 years at 8% simple interest while inflation runs at 6%
per year. What is the real gain? (Supplementary)
**A.** Amount repaid $= 1,00,000(1 + 0.08\times3) = 1,24,000$. Real value of the repayment
$= 1,24,000/(1.06)^3 = 1,24,000/1.191016 = 1,04,112$. Real gain = Rs 4,112 (the lender still gains
because 8% > 6%).
**Answer Rs 4,112 real gain.** *Check:* real return $= 1.24/1.191016 - 1 = 4.11\% \approx 8\%-6\%$.

**Q4.** Why is WPI used by producers while CPI is used by households? (Supplementary)
**A.** WPI tracks bulk/wholesale prices and therefore reflects the cost of materials entering
production; CPI tracks final retail prices of the basket a household buys, hence the cost of living.
The two differ in basket, stage of trade, and therefore in the user each serves.

---

## 12. Chapter summary

- CPI = basket cost now ÷ basket cost in base period × 100; it measures the **level** of prices.
- Inflation = **rate of change** of the CPI between two periods.
- An increase in CPI does **not itself equal** inflation (exact-repeat PYQ).
- Demand-pull (too much money), cost-push (factor prices), built-in, and their ugly combination
  stagflation.
- Nominal rate, inflation rate and real rate are linked by $(1+i) = (1+i')(1+f)$.

## 13. Revision checklist

- [ ] Can I write the CPI formula and the inflation-rate formula correctly?
- [ ] Can I answer the exact-repeat question (b) in two crisp lines?
- [ ] Can I name the three inflation types with one example each?
- [ ] Can I compute $i' = (1+i)/(1+f)-1$ for 5.5% and 2%/8%?
- [ ] Can I state three limitations of the CPI?

---

## Related notes

[02 Time Value of Money](02-Time-Value-of-Money.md) · [06 NPV/IRR/BCR](06-Investment-Appraisal-NPV-IRR-BCR.md) ·
[12 Short-Answer Bank](12-Short-Answer-Question-Bank.md) · [13 Numerical Practice](13-Numerical-Practice-Set.md) ·
[14 Formula Sheet](14-Formula-Sheet.md) · [15 Last-Minute Revision](15-Last-Minute-Revision.md)
