# 04 — Depreciation

> **Exam-critical chapter.** Depreciation appeared in **all three years**: three one-mark true/false
> items (2022-2023), a 15-mark question on the types of property (2023-2024) and a 15-mark question on
> the methods of depreciation (2024-2025).

---

## Learning objectives

After studying this chapter you should be able to:
1. Define depreciation and state its real objectives (and reject the false ones asked in the paper).
2. Distinguish depreciable cost, useful life, salvage value, book value and market value.
3. Classify property into tangible, intangible, wasting and non-depreciable categories.
4. Compute depreciation by straight-line, diminishing balance, double-declining balance,
   units-of-production and sum-of-years'-digits methods.
5. Explain the causes of depreciation (physical, functional, external).
6. Adjust a tax computation for depreciation and handle the missing tax rate correctly.

---

## 1. Prerequisites and basic concepts

- **Cost** is what you paid; **value** is what it is worth now. Depreciation is an **allocation of a
  past cost** over future periods — it is not a valuation.
- Every accounting period must carry a share of the cost of an asset that has been consumed.

---

## 2. Explanation from zero

### 2.1 Why depreciation exists

A machine costing Rs 10,00,000 that works for 5 years and then has no resale value consumes
Rs 2,00,000 of its earning capacity every year. If this consumption is not recorded:

- profit is overstated and tax is overpaid;
- the fund needed to replace the machine is never created;
- reported profit does not reflect the true economic performance of the business.

### 2.2 The objectives of depreciation (and the false statements in the paper)

**True objectives**
1. **Cost allocation / matching** — match the cost of the asset with the revenue it helps generate.
2. **Tax computation** — depreciation is an allowable expense; it reduces taxable income and tax.
3. **Replacement and renewal fund** — the accumulated depreciation provides the money to replace the
   asset when it wears out.
4. **True profit measurement** — a fair measure of profit after allowing for the consumption of assets.
5. **Valuation of assets on the balance sheet** — book value = cost − accumulated depreciation.
6. **Decision-making information** — depreciation affects cash flow, tax and profitability measures.

> **PYQ trap (2022-2023 A-X):** *"The main objective of depreciation is calculation of net profit"* —
> **False.** Net profit is an *outcome* of depreciation accounting; the objectives are cost allocation,
> tax planning, replacement funding and fair profit measurement.

### 2.3 Key terms

| Term | Definition |
|---|---|
| **Depreciable cost / depreciable amount** | Cost of the asset minus its salvage value: $DC = C - S$ |
| **Cost $C$** | Purchase price + freight + installation + other direct costs of getting it ready |
| **Salvage value $S$** | Expected proceeds from disposal at the end of useful life (also called scrap value) |
| **Useful life $n$** | Number of years (or units) over which the asset gives service |
| **Book value (carrying value)** | Cost minus accumulated depreciation: $BV = C - AD$ |
| **Market value** | The price the asset would fetch today in the market |
| **Accumulated depreciation** | Total depreciation charged over the asset's life so far |
| **Depreciable basis** | $C - S$, the amount to be spread over the life |
| **Book depreciation** | Tax rules in some countries limit depreciation to the book value; depreciation for tax may exceed book depreciation |
| **Group depreciation / composite depreciation** | One rate applied to a group of similar assets |

### 2.4 Market value vs book value — the 2022-2023 true/false trap

> *"When market value of an asset is higher than book value, then depreciation is not charged"*
> (PYQ 2022-2023, A-II) → **False.**

Depreciation is computed from **cost**, **salvage value** and **useful life**. A rise in market value
(a land boom, a bull market in machinery) does not stop the physical wear or the passage of time, so
depreciation continues unchanged. (Accounting standards in most countries also disallow revaluation
increments to be recognised in income for such assets — mention only if asked.)

> *"If adequate maintenance expenditure is incurred, there is no need of charging depreciation"*
> (PYQ 2022-2023, A-VI) → **False.** Maintenance preserves the asset's condition and its life; it does
> not remove the consumption of the asset that has already occurred. Maintenance is a period cost;
> depreciation is the allocation of capital cost.

### 2.5 Types of property (PYQ 2023-2024, C-Q7(a) [5])

| Class | Examples | Depreciated? |
|---|---|---|
| **Tangible property** | Land, buildings, plant and machinery, vehicles, furniture, fixtures | Yes, except land |
| **Intangible property** | Patents, copyrights, trademarks, licences, goodwill | Yes (over their legal/economic life) |
| **Natural resources / wasting assets** | Mines, quarries, oil wells, timber | Yes — depletion (a special form of depreciation) |
| **Land** | Freehold land | **Never depreciated** (not consumed; only the income from it is earned) |
| **Non-depreciable items** | Land, live stock in some cases, obsolete fully-depreciated assets, stock | No |

> **PYQ 2023-2024 C-Q7(b):** *"'Almost all tangible property can be depreciated'. Explain."*
> Answer: tangible property is physical and is progressively consumed in producing goods, so its cost
> should be allocated over its useful life — hence almost all tangible property (buildings, plant,
> vehicles, furniture) is depreciable. The exceptions are **land** (never consumed) and assets whose
> cost has been fully recovered.
>
> **PYQ 2023-2024 C-Q7(c):** *"'One important exception is land, which is never depreciated.' Explain."*
> Answer: land is not consumed in use and does not wear out; it merely provides a location and rental
> income. Its value may even appreciate. Therefore no depreciation is charged on land; any improvement
> works (buildings, roads) on it are depreciated separately.

### 2.6 Causes of depreciation

1. **Physical wear and tear** — use, friction, corrosion, fatigue.
2. **Obsolescence / functional (economic) depreciation** — better designs, new technology, process
   changes, change in market demand (a 10-year-old machine may be useless if the product dies).
3. **External / economic causes** — inflation, higher maintenance cost, legal or regulatory changes,
   exhaustion of nearby resources, natural calamaries.
4. **Normal obsolescence of style/colour** (for consumer goods).

### 2.7 Depreciation and taxes

Depreciation is **not a cash outflow** — it is an accounting charge. Its significance for an engineer is
that it **reduces taxable income**, thereby saving tax:

$$\text{Taxable income} = \text{Revenue} - \text{Operating expenses (excl. depreciation)} - \text{Depreciation}$$

$$
\text{Tax} = \text{Taxable income} \times \text{applicable tax rate}
$$

> **PYQ 2023-2024, C-Q9(a)(iii)** asks for "the federal income taxes for the year" but the paper
> prints **no tax rate**. Correct practice: give the general form
> $\text{Tax} = \text{Taxable income} \times \text{rate}$, state that the rate is **not supplied in the
> question**, and then show the arithmetic using the textbook assumption of 35% clearly labelled as an
> assumption.

---

## 3. Formulas, variables and units

| Method | Formula | Variables |
|---|---|---|
| **Straight-line (SLM)** | $D = \dfrac{C - S}{n}$ | $C$ cost (Rs), $S$ salvage (Rs), $n$ life (years), $D$ annual depreciation (Rs/yr) |
| SLM book value after $t$ years | $BV_t = C - tD$ | $BV_t$ Rs |
| SLM rate | $r = \dfrac{100(C-S)}{nC}$ | $r$ % of original cost per year |
| **Diminishing balance (DB)** | $D_t = BV_{t-1}\times d$ | $BV_{t-1}$ book value at start of year (Rs), $d$ rate (decimal) |
| DB book value | $BV_t = BV_{t-1}(1-d)$ | Rs |
| **Double-declining balance (DDB)** | $D_t = 2 \times \dfrac{C}{n} \times BV_{t-1}$ | $2C/n$ = SLM rate × 2 |
| **Units of production (UOP)** | $D_t = \dfrac{C - S}{N_{total}} \times N_t$ | $N_{total}$ total lifetime units, $N_t$ units produced in year $t$ |
| **Sum of years' digits (SYD)** | $D_t = \dfrac{(N - t + 1)(N + 2)}{2} \times \dfrac{C-S}{N}$ | $N = n$ years; remaining-life fraction $\times$ depreciable cost |
| **Book value** | $BV = C - \text{accumulated depreciation}$ | Rs |
| **Straight-line equivalent of DB** | $d = 1 - (S/C)^{1/n}$ | rate that gives the same final book value |

---

## 4. The five methods, one by one

### 4.1 Straight-line method (SLM)

Equal depreciation every year. Simple, easy to understand, good for assets whose consumption is
uniform (buildings, offices, some machinery). Criticisms: ignores that new assets lose value faster
in early years, and ignores interest on the capital tied up.

### 4.2 Diminishing-balance method (DB)

A fixed percentage of the **book value** (written-down value) is written off each year, so depreciation
falls over time. Never reaches zero without an adjustment in the final year; the rate is often chosen
so that the book value at the end equals salvage value: $d = 1 - (S/C)^{1/n}$.

### 4.3 Double-declining balance (DDB)

Rate $= 2 \times$ the straight-line rate $= 2C/n$, applied to the book value, ignoring salvage until
the last year. The final book value is never below salvage: switch to straight line when that gives a
higher charge.

### 4.4 Units-of-production (UOP)

Depreciation is proportional to actual usage or output — right for plant used by machine hours, tonnes
processed, or kilometres run (see the taxi problem in [Chapter 13](13-Numerical-Practice-Set.md)).

### 4.5 Sum-of-years'-digits (SYD)

Accelerating depreciation: the numerator is the remaining life in years and the denominator is the sum
$1+2+\dots+n = n(n+1)/2$. Front-loads the charge but keeps the book value above salvage throughout.

---

## 5. Worked examples

### 5.1 Example 1 — straight line

**Given:** machine cost Rs 6,00,000, installation Rs 40,000, salvage Rs 60,000, life 8 years.
**Required:** annual depreciation, book value after 3 years, and the depreciation rate on original cost.
**Formula:** $D = (C-S)/n$; $BV_t = C - tD$; $r = 100(C-S)/(nC)$.
**Substitution:** $C = 6,40,000$; $D = (6,40,000 - 60,000)/8 = 5,80,000/8 = 72,500$.
$BV_3 = 6,40,000 - 3(72,500) = 6,40,000 - 2,17,500 = 4,22,500$.
$r = 100(5,80,000)/(8 \times 6,40,000) = 11.328\%$.
**Answer:** depreciation **Rs 72,500 per year**; book value after 3 years **Rs 4,22,500**; rate
**11.33% of original cost p.a.**
**Reasonableness check:** total depreciation over 8 years = 8 × 72,500 = Rs 5,80,000, leaving exactly the
salvage value of Rs 60,000.

### 5.2 Example 2 — diminishing balance

**Given:** asset cost Rs 2,00,000, salvage Rs 20,000, life 5 years. DB rate to be derived.
**Formula:** $d = 1-(S/C)^{1/n}$; $D_t = BV_{t-1}d$.
**Substitution:** $d = 1 - (20,000/200,000)^{1/5} = 1 - (0.1)^{0.2} = 1 - 0.63096 = 0.36904$ (36.90%).
Year 1: $D_1 = 2,00,000 \times 0.36904 = 73,808$, $BV_1 = 1,26,192$.
Year 2: $D_2 = 1,26,192 \times 0.36904 = 46,537$, $BV_2 = 79,655$.
**Answer:** DB rate **36.90% p.a.**; year-1 depreciation **Rs 73,808**; year-2 **Rs 46,537**;
book values Rs 1,26,192 and Rs 79,655.
**Reasonableness check:** the falling book value converges to the Rs 20,000 salvage value at year 5,
and depreciation declines each year as expected.

### 5.3 Example 3 — double-declining balance with switch to SLM

**Given:** cost Rs 5,00,000, salvage Rs 50,000, life 10 years.
**Formula:** $D_t = 2(C/n)BV_{t-1}$; compare with SLM on remaining book value over remaining life.
**Substitution:** SLM rate = 10%; DDB rate = 20%.
Year 1: $D_1 = 0.20 \times 5,00,000 = 1,00,000$; $BV_1 = 4,00,000$.
Year 2: $D_2 = 0.20 \times 4,00,000 = 80,000$; $BV_2 = 3,20,000$.
Year 3: $D_3 = 0.20 \times 3,20,000 = 64,000$; $BV_3 = 2,56,000$.
(Switch test at the end of year 3: SLM on remaining Rs 2,56,000 over 7 years = 36,571 per year vs DDB
year-4 charge = 51,200, so continue DDB while DDB is larger; the switch year is where the SLM on the
remaining book value exceeds the DDB charge.)
**Answer:** DDB rate **20%**; year-1, 2, 3 charges **Rs 1,00,000 / 80,000 / 64,000**; book values
**Rs 4,00,000 / 3,20,000 / 2,56,000**.
**Reasonableness check:** depreciation declines but book value stays above the Rs 50,000 salvage value.

### 5.4 Example 4 — units of production

**Given:** a taxi costing Rs 75,000 with salvage Rs 15,000, total life 3,00,000 km. In year 1 it runs
48,000 km.
**Formula:** $D = \dfrac{C-S}{N_{total}}N_t$.
**Substitution:** depreciation per km $= (75,000-15,000)/3,00,000 = 0.20$ Rs/km.
$D_1 = 48,000 \times 0.20 = 9,600$.
**Answer:** depreciation per kilometre **Rs 0.20**; year-1 depreciation **Rs 9,600**; book value
Rs 65,400.
**Reasonableness check:** over the full life, 3,00,000 km × Rs 0.20 = Rs 60,000 = cost − salvage.

### 5.5 Example 5 — sum of years' digits

**Given:** cost Rs 1,00,000, salvage Rs 10,000, life 4 years.
**Formula:** $D_t = \frac{(N-t+1)(N+2)}{2}\times\frac{C-S}{N}$; sum of digits $= 4+3+2+1 = 10$.
**Substitution:** depreciable cost $= 90,000$; per digit share $= 9,000$.
$D_1 = 4 \times 9,000 = 36,000$; $D_2 = 3 \times 9,000 = 27,000$; $D_3 = 2 \times 9,000 = 18,000$;
$D_4 = 1 \times 9,000 = 9,000$.
**Answer:** **Rs 36,000 / 27,000 / 18,000 / 9,000**; book values Rs 64,000, 37,000, 19,000, 10,000.
**Reasonableness check:** the four charges total Rs 90,000 = cost − salvage, and each year's book value
stays at or above salvage.

### 5.6 Example 6 — the 2023-2024 bonus depreciation problem (PYQ)

**Given:** new processing and packaging equipment purchased for $800,000; sales revenue for the year
$1,250,000; operating expenses (excluding capital expenditure) $360,000; equipment qualifies for 100%
bonus depreciation.
**Required:** (i) first-year depreciation charge; (ii) first-year taxable income; (iii) federal income
taxes for the year.
**Formula:** bonus depreciation = 100% of first cost; taxable income = sales − operating expenses −
depreciation; tax = taxable income × applicable rate.
**Substitution (i):** $D = 1.00 \times 800,000 = 800,000$; book value after the charge = $0.
**(ii):** taxable income $= 1,250,000 - 360,000 - 800,000 = 90,000$.
**(iii):** *The paper prints no tax rate.* General form: $\text{Tax} = 90,000 \times t$. Using the
textbook assumption $t = 35\%$: $90,000 \times 0.35 = 31,500$.
**Answer:** (i) **$800,000**; (ii) **$90,000**; (iii) **$31,500 at an assumed 35% rate — the rate is
not given in the question, so state the assumption**.
**Reasonableness check:** with full bonus depreciation the tax base falls to $90,000, so the tax bill is
much smaller than on $890,000 of profit (which would be $311,500 at 35%).

---

## 6. Common mistakes and how to avoid them

| Mistake | Why wrong | Correction |
|---|---|---|
| Using market value instead of cost in the depreciation base | Depreciation follows cost, not market value | Use $C - S$ |
| Forgetting installation cost in $C$ | Understates depreciation | $C$ = invoice + freight + installation + commissioning |
| Ignoring salvage in the straight-line formula | Overstates depreciation | Always subtract $S$ |
| Applying DB rate to the original cost every year | DB is on written-down value | Use $BV_{t-1}$ |
| Letting DDB book value fall below salvage | Over-depreciation | Switch to SLM in the final years |
| Charging depreciation on land | Land is not consumed | Never depreciate land |
| Treating depreciation as a cash outflow in NPV | It is a non-cash charge | Add it back in cash-flow analysis; use it only for tax |
| Guessing a tax rate | Fabricates data | State "rate not given"; give the general form |

---

## 7. Likely one-mark questions with answers

| Question | Answer |
|---|---|
| When market value of an asset is higher than book value, depreciation is not charged (T/F) (PYQ 2022-2023, A-II) | **False** — depreciation is based on cost, salvage value and useful life, not market value |
| If adequate maintenance expenditure is incurred, there is no need of charging depreciation (T/F) (PYQ 2022-2023, A-VI) | **False** — maintenance preserves the asset; depreciation must still be charged |
| The main objective of depreciation is calculation of net profit (T/F) (PYQ 2022-2023, A-X) | **False** — its objectives are cost allocation, tax computation, replacement funding and fair profit measurement |
| What is book value? (Supplementary) | Cost of the asset less accumulated depreciation |
| Define salvage value. (Supplementary) | The estimated proceeds from disposing of the asset at the end of its useful life |
| Why is land not depreciated? (PYQ 2023-2024, C-Q7(c)) | Land is not consumed in use and does not wear out; only improvements on it are depreciated |
| What is depreciation? (PYQ 2024-2025, C-Q9) | Systematic allocation of the depreciable cost of a tangible/intangible asset over its useful life |
| Name two causes of depreciation. (Supplementary) | Physical wear and tear; obsolescence (functional/economic) |

---

## 8. Five-mark theory answers in exam-ready format

### Q. Write a short note on expenditures for depreciable assets by the business firms. (PYQ 2022-2023, B-Q4)

1. **Meaning.** Expenditures on depreciable assets are the outlays a firm makes on property, plant and
   equipment (machinery, buildings, vehicles, furniture) that will be used for more than one accounting
   period and whose cost is therefore spread over several years.
2. **Components of cost.** Purchase price, freight and insurance, installation and commissioning,
   site preparation, and initial test runs — all capitalised as part of the depreciable cost.
3. **Classification.** Additions to existing assets, replacements, and major overhauls that extend
   useful life are capitalised; routine repairs and maintenance are charged to revenue.
4. **Treatment.** The expenditure is not expensed in the year incurred; it is shown as an asset on the
   balance sheet and written off gradually as depreciation over the asset's useful life.
5. **Purpose and effect.** Capital expenditure supports future benefits and is matched to them; it does
   not reduce current profit, but it reduces future profit through depreciation and may reduce tax.
6. **Conclusion.** Such expenditure is one of the largest cash outflows of an engineering project and
   must be estimated carefully before an investment decision is taken.

### Q. Explain the types of property in the context of depreciation. (PYQ 2023-2024, C-Q7(a) [5])

1. **Tangible property** — physical assets: land, buildings, plant and machinery, vehicles, furniture;
   depreciated over useful life (except land).
2. **Intangible property** — non-physical rights: patents, copyrights, trademarks, licences, goodwill;
   depreciated (amortised) over their legal or economic life.
3. **Natural resources / wasting assets** — mines, oil wells, quarries, forests; the depletion of the
   asset is charged as depreciation.
4. **Land** — never depreciated because it is not consumed in use.
5. **Fully depreciated / obsolete assets** — carried at nil book value; no further depreciation.
6. (Conclusion.) The classification determines whether depreciation applies and over what period.

---

## 9. Fifteen-mark answer structure where applicable

**Q. "What do you mean by depreciation? Explain the different methods of calculation of depreciation."**
(PYQ 2024-2025, C-Q9, printed internal split **5 + 10**)

| Marks | Content to write |
|---|---|
| 5 | Definition (1), why it is needed (1), objectives (1), key terms: depreciable cost, salvage, useful life, book value (2) |
| 2 | Straight-line: formula + one-line merits/demerits |
| 2 | Diminishing balance: formula + one-line merits/demerits |
| 2 | Double-declining balance: formula + switch rule |
| 2 | Units of production: formula + typical use |
| 1 | Sum of years' digits: formula + note |
| 1 | Comparison table (which method suits which asset) + conclusion |

Use the working shown in Section 5 for one mini example of each method.

---

## 10. PYQ references

| Year | Question | Concept |
|---|---|---|
| 2022-2023 | A-II, A-VI, A-X | Market value vs book value; maintenance vs depreciation; purpose of depreciation |
| 2022-2023 | B-Q4 | Expenditures on depreciable assets |
| 2023-2024 | C-Q7(a,b,c) | Types of property; almost all tangible property depreciated; land never depreciated |
| 2023-2024 | C-Q9(a) | Bonus depreciation, taxable income, tax (rate not printed — flagged) |
| 2024-2025 | C-Q9 | Depreciation: meaning and methods of calculation |

---

## 11. Practice questions with answers and explanations

**Q1.** An asset costs Rs 4,00,000 with a salvage value of Rs 40,000 and a 5-year life. Compute SLM and
DB (rate 30%) depreciation for the first two years. (Supplementary)
**A.** SLM $= (4,00,000-40,000)/5 = 72,000$ per year.
DB: $D_1 = 4,00,000 \times 0.30 = 1,20,000$, $BV_1 = 2,80,000$; $D_2 = 2,80,000 \times 0.30 = 84,000$,
$BV_2 = 1,96,000$.
**Answer:** SLM Rs 72,000/yr; DB Rs 1,20,000 then Rs 84,000.
*Check:* DB is front-loaded and ends nearer the salvage value; the total depreciation over 5 years at
30% leaves $4,00,000(0.7)^5 = 67,200$, which is above the Rs 40,000 salvage, so a final adjustment
would be needed.

**Q2.** A machine has a book value of Rs 3,00,000 and a remaining life of 5 years with a salvage value
of Rs 20,000. Find depreciation for year 1 under SLM. (Supplementary)
**A.** $(3,00,000 - 20,000)/5 = 56,000$. **Answer Rs 56,000.**
*Check:* the depreciable amount must exclude salvage, and must use book value (not original cost),
because depreciation continues on the remaining book value.

**Q3.** State whether depreciation is a cash flow and explain its significance. (Supplementary)
**A.** No — it is a non-cash accounting charge. Its significance is (i) it reduces taxable income and
therefore tax (a real cash saving), (ii) it measures the consumption of the asset, and (iii) it funds
replacement. In cash-flow analysis, depreciation is added back after tax.

---

## 12. Chapter summary

- Depreciation = allocation of depreciable cost $(C-S)$ over the useful life.
- Depreciation is based on cost and life — **never on market value**.
- Land is never depreciated; almost all other tangible property is.
- Five methods: SLM, DB, DDB, units-of-production, SYD — know one formula and one merit each.
- Depreciation cuts taxable income; it is not itself a cash outflow.

## 13. Revision checklist

- [ ] Can I write the depreciable-cost, book-value and salvage-value definitions?
- [ ] Can I answer the three 2022-2023 true/false items correctly with one reason each?
- [ ] Can I compute SLM, DB, DDB, UOP and SYD depreciation for a small example?
- [ ] Can I explain why land is not depreciated (C-Q7c)?
- [ ] Can I handle the missing tax rate in 2023-2024 C-Q9(a)(iii) correctly?

---

## Related notes

[01 Basics](01-Basics-and-Engineering-Economy.md) · [05 Cost Accounting](05-Cost-Accounting-and-Break-Even.md) ·
[09 Financial Statements](09-Financial-Statements.md) · [13 Numerical Practice](13-Numerical-Practice-Set.md) ·
[14 Formula Sheet](14-Formula-Sheet.md) · [15 Last-Minute Revision](15-Last-Minute-Revision.md)
