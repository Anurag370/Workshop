# 01 — Basics and Engineering Economy

> **Source note.** Concepts in this chapter are standard engineering-economy fundamentals
> (Supplementary), tied to the questions actually printed in the three papers. PYQ references are given
> in the form `(PYQ 2022-2023, A-IV)`.

---

## Learning objectives

After studying this chapter you should be able to:
1. Explain what engineering economics is and why an engineer needs it.
2. Use the language of scarcity, choice, opportunity cost and the margin.
3. Explain the difference between economic profit and accounting profit.
4. List the steps of the engineering-economy cycle.
5. Distinguish fixed / variable / direct / indirect / sunk / incremental / opportunity costs.
6. Explain the different types of cost estimates and their accuracy.
7. Answer the one-mark Group-A items on rate of return, risk–return and working capital.

---

## 1. Prerequisites and basic concepts

You need only three things from arithmetic: percentages, ratios and powers.

### 1.1 Scarcity, choice and opportunity cost

- **Scarcity** — human wants are unlimited, resources (land, labour, capital, enterprise) are limited.
- **Choice** — every use of a scarce resource rules out its next best use.
- **Opportunity cost** — the value of the *next best alternative given up*. It is the real cost of a decision.

> Example (Supplementary): a company uses Rs 10,00,000 of its own cash to buy a new machine.
> Accounting records show a cost of Rs 10,00,000. If the same cash could have earned 12% in a bank,
> the opportunity cost of the machine is Rs 10,00,000 + Rs 1,20,000 interest = **Rs 11,20,000**.

### 1.2 The economic problem and the margin

Every engineering decision is a "how much" question: how much capacity, how much capital, how many
units. Economics helps because resources are scarce. Decisions are made **at the margin** — the gain
from one more unit must be compared with the extra cost of that unit.

### 1.3 The firm and its objective

| Objective | Meaning |
|---|---|
| Profit maximisation | Choose the output level where marginal revenue = marginal cost (economic approach) |
| Value maximisation | Increase the market value of the firm (shareholders' wealth) |
| Sales maximisation | A manager's preference; not generally profit-maximising |

In engineering economy we normally use a **decision criterion** (NPV, IRR, BCR, break-even) rather than
a single profit number, because the criterion can include risk, time and scale.

### 1.4 Economic profit vs accounting profit

| | Economic profit | Accounting profit |
|---|---|---|
| Definition | Total revenue − (explicit costs + implicit costs) | Total revenue − explicit accounting costs |
| Implicit costs | Included: owner's salary foregone, interest on own capital, rent of owned premises | Excluded |
| Use | True economic performance, project appraisal | Statutory reporting, tax, dividend policy |

> Exam line: *"Economic profit is revenue less all opportunity costs (explicit and implicit); accounting
> profit ignores implicit costs and therefore usually overstates economic performance."*

### 1.5 Interest and risk as costs

- **Interest** is the cost of using someone else's (or one's own) capital. It converts future benefits
  into comparable present values (see [Chapter 02](02-Time-Value-of-Money.md)).
- **Risk** is the chance that actual cash flows differ from expected ones. Risk must be rewarded with a
  higher expected rate of return, otherwise no rational investor will take it.

---

## 2. Explanation from zero: what engineering economics is

**Engineering economics** is the application of economic principles — cost, benefit, time, risk and
uncertainty — to engineering problems so that alternatives can be compared objectively.

Why a B.Tech student needs it:
1. Almost every professional decision has a money dimension (buy or lease, make or buy, new line or
   repair).
2. Exams and interviews test structured thinking: *state the objective → list alternatives → estimate
   cash flows → apply a criterion → recommend*.
3. It converts a vague "good idea" into a defensible recommendation with numbers.

**The engineering-economy cycle (Supplementary, standard framework)**

```
Problem recognition → Evaluation of alternatives → Development of cash flows
        ↑                                              ↓
Monitoring & control ← Decision & implementation ←  Economic analysis (discounting)
```

1. **Problem recognition** — define the need; "What decision is actually required?"
2. **Feasibility/alternative generation** — list every technically feasible way forward.
3. **Estimation of cash flows** — costs, revenues, life, salvage, working capital, taxes.
4. **Economic analysis** — apply PW, FW, NPV, IRR, BCR, break-even.
5. **Decision and implementation** — choose, fund, execute, monitor.
6. **Monitoring and control** — compare actual with estimated; correct if needed.

> **PYQ link** — 2022-2023 Group B Q6: *"'Estimation is the foundation of economic analysis' — Explain."*
> The examiner wants: without a reliable estimate of costs, life, revenues and timing, no economic
> method can discriminate between alternatives, and the "best" project on paper may be the worst in
> practice. Estimation precedes analysis.

---

## 3. Important terminology and definitions

| Term | Definition (exam-safe wording) |
|---|---|
| **Cost** | The value of the resources consumed to achieve an objective. |
| **Fixed cost** | Cost that does not change with the level of output within the relevant range (rent, salary). |
| **Variable cost** | Cost that changes in direct proportion to output (material per unit, power per unit). |
| **Semi-variable cost** | Partly fixed, partly variable (e.g. electricity bill with a fixed charge + unit charge). |
| **Direct cost** | Cost traceable directly to a product or job (direct material, direct labour). |
| **Indirect cost** | Cost incurred for the business as a whole and not directly traceable (rent, administration, factory overhead). |
| **Sunk cost** | A cost already incurred and unrecoverable; it must be **ignored** in decisions. |
| **Opportunity cost** | Value of the next best alternative forgone. |
| **Incremental (differential) cost** | The difference between two alternatives; used for "make or buy", expansion decisions. |
| **Avoidable cost** | Cost that disappears if a project is rejected. |
| **Marginal cost** | The additional cost of producing one more unit. |
| **Opportunity revenue (gain)** | Benefit forgone by not choosing the next best alternative. |
| **Working capital** | Current assets − current liabilities; short-term liquidity of a business. |
| **Minimum acceptable rate of return (MARR)** | The lowest rate of return that makes an investment acceptable to the decision-maker; also called the hurdle rate or cost of capital. |
| **Accounting rate of return** | Average annual profit ÷ average investment (a simple, non-discounting measure). |
| **Benchmarking (BEM)** | Estimating by scaling from a known similar plant/process. |
| **Capacity** | Maximum output a system can produce under stated conditions. |

---

## 4. Formulas and what each variable means

| Formula | Variables and units | When to use |
|---|---|---|
| Contribution $= S - VC$ | $S$ = sales (Rs), $VC$ = variable cost (Rs) | Any break-even or target-profit question ([Ch. 05](05-Cost-Accounting-and-Break-Even.md)) |
| P/V ratio $= \dfrac{S - VC}{S}$ | ratio or % | Break-even from sales data |
| BEP (units) $= \dfrac{FC}{SP - VC}$ | $FC$ = fixed cost (Rs/yr), $SP$ = selling price (Rs/unit) | Break-even in units |
| BEP (sales) $= \dfrac{FC}{\text{P/V ratio}}$ | $FC$ (Rs/yr) | Break-even in rupees |
| Average fixed cost/unit $= \dfrac{FC}{Q}$ | $Q$ = units produced (units) | 2024-2025 Group A item XII |
| Opportunity cost of owned resource = market rent/interest it could earn | Rs/yr | Make-or-buy, use of own funds |
| Accounting profit $= R - \text{explicit costs}$ | $R$ = revenue (Rs) | Financial statements ([Ch. 09](09-Financial-Statements.md)) |
| Economic profit $= R - (\text{explicit} + \text{implicit costs})$ | Rs | True performance of a project |

---

## 5. Step-by-step derivations when useful

### 5.1 Why fixed costs are "per unit" costs that fall with volume

Total fixed cost $FC$ does not change. Therefore per-unit fixed cost $AFC$ is

$$AFC = \frac{FC}{Q}$$

So halving $Q$ doubles the fixed cost per unit (2024-2025 Group A item XII is a direct test of this).

### 5.2 Why the rate of return is the "price" of money

If a project earns exactly the minimum expected rate of return, the investor is neither better nor worse
off than lending the money at a safe rate. Hence the minimum expected rate of return acts as a hurdle;
a project must beat it to be worth doing.

---

## 6. Worked examples

### 6.1 Example 1 — opportunity cost and economic profit (Supplementary)

**Given:** A workshop earns Rs 4,00,000 revenue in a year. Explicit costs: material Rs 1,50,000,
labour Rs 1,00,000, rent Rs 30,000, power Rs 20,000. The owner forgoes a salary of Rs 3,60,000 by
running the workshop, and the capital of Rs 5,00,000 could have earned 10% interest.
**Required:** accounting profit and economic profit.
**Formula:** Accounting profit $= R - \text{explicit costs}$; Economic profit $= R - (\text{explicit} + \text{implicit})$.
**Substitution:** Accounting profit $= 4,00,000 - (1,50,000+1,00,000+30,000+20,000) = 4,00,000 - 3,00,000 = 1,00,000$.
Implicit costs $= 3,60,000 + 0.10 \times 5,00,000 = 3,60,000 + 50,000 = 4,10,000$.
Economic profit $= 4,00,000 - (3,00,000 + 4,10,000) = -3,10,000$.
**Answer:** Accounting profit = **Rs 1,00,000**; Economic profit = **−Rs 3,10,000 (a loss of Rs 3,10,000)**.
**Reasonableness check:** economic profit is lower than accounting profit whenever implicit costs exist; a
negative value means the capital and labour are better used elsewhere.

### 6.2 Example 2 — average fixed cost per unit (2024-2025 Group A item XII)

**Given:** Production 780,000 units; fixed costs Rs 32 lac (Rs 32,00,000); variable cost Rs 16/unit.
**Required:** average fixed cost per unit.
**Formula:** $AFC = \dfrac{FC}{Q}$.
**Substitution:** $AFC = \dfrac{32,00,000}{780,000} = 41.0256$.
**Answer:** **Rs 41.03 per unit** (about Rs 41).
**Reasonableness check:** at Rs 16 variable cost, AFC of Rs 41 is larger than variable cost per unit,
which is normal for a high-volume, capital-intensive product line.
*(Full solution with the average total cost is in [Chapter 05](05-Cost-Accounting-and-Break-Even.md).)*

### 6.3 Example 3 — sunk cost principle (Supplementary)

**Given:** A company paid Rs 5,00,000 for a machine last year. A new model costs Rs 6,00,000 and would
save Rs 2,00,000 per year in operating cost.
**Required:** should the old machine be replaced now?
**Formula/Reasoning:** the Rs 5,00,000 already spent is a **sunk cost** and is irrelevant. Compare only
future flows: incremental cost Rs 6,00,000 against annual savings Rs 2,00,000 (plus any salvage value of
the old machine, which is a future cash flow and must be included).
**Answer:** the Rs 5,00,000 must not enter the decision; the comparison is Rs 6,00,000 (less salvage of
old machine) against the savings stream.
**Reasonableness check:** if the Rs 5,00,000 were included, the project would look worse and the
decision would be distorted.

---

## 7. Common mistakes and how to avoid them

| Mistake | Why it is wrong | Correction |
|---|---|---|
| Including sunk costs in a replacement decision | Money already spent cannot be recovered | List only future cash flows |
| Treating opportunity cost as zero | Ignores the value of the next best use | Add the forgone benefit |
| Using accounting profit for economic decisions | Misses implicit costs | Use cash flow + discounting |
| Confusing fixed cost with "constant forever" | Fixed cost is constant only in the **relevant range** | State the range (e.g. 2,000–6,000 units) |
| Confusing average fixed cost with marginal fixed cost | AFC falls as volume rises; MFC = 0 | Use AFC = FC/Q only |
| Writing "profit is the objective of engineering economics" | The objective is the best economic decision under constraints | State the decision criterion used |

---

## 8. Likely one-mark questions with answers

| Question | Answer |
|---|---|
| The cash flows method, utilized by the internal rate of return and net present value method is known as ______ (PYQ 2022-2023, A-IV) | **Discounted cash-flow (DCF) technique** |
| The minimum expected rate of return that is needed to persuade an investor to purchase the security at given risk is a rate of return (T/F) (PYQ 2022-2023, A-IX) | **True** — it is the minimum acceptable rate of return (hurdle rate) |
| The degree of correlation between risk and return over a longer period of time is generally believed to be as highly positive (T/F) (PYQ 2022-2023, A-XII) | **False** — higher risk must be matched by a higher expected return, but the relationship is weak, not highly positive |
| What is Working Capital? (PYQ 2022-2023, A-XI) | Current assets minus current liabilities — the short-term liquidity of a business |
| Cash flow is an example of an investment activity and is also considered as "Sale of Investment by Non-Financial Enterprise" (T/F) (PYQ 2022-2023, A-VIII) | **True** — it is an investing-activity cash flow |
| Define opportunity cost. (Supplementary) | Value of the next best alternative forgone by a decision |
| Define sunk cost. (Supplementary) | A cost already incurred and unrecoverable; irrelevant to current decisions |
| What is MARR? (Supplementary) | Minimum acceptable rate of return — the hurdle rate for an investment |
| Define an implicit cost. (Supplementary) | A non-monetary cost of using the firm's own resources (e.g. owner's salary, interest on own capital) |
| What is the engineering-economy cycle? (Supplementary) | Problem recognition → alternative evaluation → cash-flow estimation → economic analysis → decision and implementation → monitoring and control |

---

## 9. Five-mark theory answers in exam-ready format

### Q. "Estimation is the foundation of economic analysis" — Explain. (PYQ 2022-2023, B-Q6)

1. **Meaning:** Economic analysis can only rank alternatives if the cash flows attached to them are
   estimated credibly; estimation converts physical and financial data into money values.
2. **Estimation is the first step** in the engineering-economy cycle; without it no PW, NPV, IRR or BCR
   calculation can begin.
3. **What must be estimated:** equipment cost (installed), capacity, operating life and salvage value,
   material, labour and overhead consumption, selling price and demand, working capital, financing and
   tax, and the timing of all cash flows.
4. **Why it matters:** a 10% error in the estimated cost of a 10-year project can easily exceed the
   entire margin between two alternatives — the better-estimated project is often the better project.
5. **Link to estimation quality:** better data (quotes, vendor data, analogous plants, BEM) reduces
   uncertainty; where data are weak, use a range and sensitivity analysis rather than a single number.
6. **Conclusion:** estimation quality sets the accuracy of every economic result; therefore estimation is
   the foundation of economic analysis.

### Q. Distinguish between accounting profit and economic profit. (Supplementary, 5 marks)

| Basis | Accounting profit | Economic profit |
|---|---|---|
| Definition | Revenue − explicit accounting costs | Revenue − explicit − implicit costs |
| Implicit costs | Ignored | Included (owner's salary, interest on capital) |
| Basis of decision | Statutory/tax reporting | Investment and project decisions |
| Result | Usually higher | Lower or negative |
| Use | Dividends, statutory accounts | Correct choice of project/alternative |

**Conclusion:** accounting profit answers "what does the law require us to report?"; economic profit
answers "was the decision economically sensible?".

### Q. Explain the steps of the engineering-economy cycle. (Supplementary, 5 marks)

Problem recognition → feasibility study and generation of alternatives → estimation of cash flows
(costs, revenues, life, salvage, working capital) → economic analysis using discounting/criteria →
decision and implementation → monitoring, control and post-evaluation, with feedback to step 1.
Add one sentence for each step; conclude that the cycle is iterative, not one-way.

---

## 10. Fifteen-mark answer structure where applicable

**Q. "Prepare an economic evaluation of a proposed expansion."** (Supplementary model structure)

| Marks | Content |
|---|---|
| 2 | Problem statement and objective (what decision, what constraints) |
| 2 | Alternative generation (do nothing, expand, outsource, replace) |
| 3 | Estimation of cash flows: capital cost, operating costs, revenues, life, salvage, working capital, taxes |
| 3 | Economic analysis: discount rate (MARR), PW of benefits and costs, NPV, IRR, BCR |
| 2 | Risk and sensitivity: break-even, sensitivity of NPV to key variables |
| 2 | Risk/scenario analysis |
| 1 | Recommendation, justification and monitoring plan |

---

## 11. PYQ references using this chapter's concepts

| Year | Question | Concept |
|---|---|---|
| 2022-2023 | A-IV | DCF technique used by NPV/IRR |
| 2022-2023 | A-IX | Minimum expected rate of return |
| 2022-2023 | A-XI | Working capital |
| 2022-2023 | A-XII | Risk–return correlation |
| 2022-2023 | B-Q6 | Estimation is the foundation of economic analysis |
| 2023-2024 | A-V | Decision tree algorithm family (supervised learning) |
| 2023-2024 | A-IX | Diversification turns two risky securities into a riskless portfolio (perfect negative correlation) |
| 2024-2025 | A-XII | Average fixed cost per unit |
| 2024-2025 | A-VI | "Defender" in replacement analysis = existing equipment |

---

## 12. Practice questions with answers and explanations

**Q1.** A machine costs Rs 2,00,000 and yields Rs 60,000 per year for 5 years. The capital could earn
8% interest. Is the machine worth buying? (Supplementary)
**A.** Compare present worth of Rs 60,000 for 5 years at 8% (P/A = 3.9927) = Rs 2,39,562 with the cost
Rs 2,00,000; NPV = **+Rs 39,562 > 0**, so buy. Reason: the inflow stream is worth more than the price.

**Q2.** Identify the sunk cost in each case: (i) Rs 50,000 spent on a market survey last year; (ii)
Rs 10,000 monthly electricity bill of the present factory; (iii) the Rs 2,00,000 book value of an old
machine being replaced. (Supplementary)
**A.** (i) sunk; (ii) not sunk (recurring future cost); (iii) not strictly sunk — its *market value
today* (a future cash flow) matters, though its book value does not.

**Q3.** A firm's total cost is Rs 10,00,000 at 4,000 units and Rs 14,00,000 at 8,000 units. Find the
fixed and variable cost per unit. (Supplementary)
**A.** Let $FC + VC_{u} Q$ be total cost. At 4,000 units: $FC + 4,000 v = 10,00,000$; at 8,000 units:
$FC + 8,000 v = 14,00,000$. Subtract: $4,000 v = 4,00,000 \Rightarrow v = 100$; then
$FC = 10,00,000 - 4,00,000 = 6,00,000$. Answer: **variable cost Rs 100/unit; fixed cost Rs 6,00,000**
(AFC falls from Rs 150 to Rs 75 per unit).

**Q4.** Explain, in three lines, why fixed cost per unit falls as production rises.
**A.** Fixed cost in total is constant, so it is spread over more units; $AFC = FC/Q$ therefore falls
hyperbolically with $Q$. This is why high-volume production enjoys a cost advantage (economies of
scale, see [Chapter 07](07-Cost-Estimation-and-Learning-Curve.md)).

---

## 13. Chapter summary

- Engineering economics compares alternatives under scarcity using money, time and risk.
- Opportunity cost and sunk cost are the two cost ideas examiners test most often.
- Economic profit subtracts implicit costs; accounting profit does not.
- The cycle is: recognise → estimate → analyse → decide → implement → monitor.
- Estimation quality drives the reliability of every economic result.
- Cost vocabulary (fixed, variable, direct, indirect, sunk, incremental) is used in every later chapter.

## 14. Revision checklist

- [ ] Can I explain scarcity → choice → opportunity cost in 3 sentences?
- [ ] Can I distinguish economic and accounting profit with a table?
- [ ] Can I draw the engineering-economy cycle from memory?
- [ ] Do I know the answer to "depreciation is charged on market value or book value"? (book value — see [Ch. 04](04-Depreciation.md))
- [ ] Do I know $AFC = FC/Q$ and can I compute Rs 41.03 for the 2024-2025 item?
- [ ] Can I explain in one line why sunk costs are ignored?

---

## Related notes

[00 PYQ Analysis](00-PYQ-Analysis.md) · [02 Time Value of Money](02-Time-Value-of-Money.md) ·
[04 Depreciation](04-Depreciation.md) · [05 Cost Accounting](05-Cost-Accounting-and-Break-Even.md) ·
[07 Cost Estimation](07-Cost-Estimation-and-Learning-Curve.md) · [10 Decision Making](10-Engineering-Decision-Making.md) ·
[12 Short-Answer Bank](12-Short-Answer-Question-Bank.md) · [14 Formula Sheet](14-Formula-Sheet.md) ·
[15 Last-Minute Revision](15-Last-Minute-Revision.md)
