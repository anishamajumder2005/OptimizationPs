# OptimizationPs
# 🏙️ Axion Prime: Minimum Cost Zoning Polygon

## 📜 Problem Statement

You are the chief architect of **Axion Prime**, a futuristic mega-city undergoing a redevelopment phase. The city is laid out on a 2D grid and contains **N buildings**, each at a certain coordinate with an associated cost weight (which may be **negative or positive**).

Your task is to **design an axis-aligned, simple (non-self-intersecting), closed polygon** that encloses **at least K buildings** and minimizes the **total cost**.

### Total Cost Formula:
Total Cost = Perimeter of Polygon + Sum of Weights of Enclosed Buildings

yaml
Copy
Edit

---

## 📥 Input Format

N K
x1 y1 w1
x2 y2 w2
...
xN yN wN

yaml
Copy
Edit

- `N`: Total number of buildings (1 ≤ K ≤ N ≤ 10000)
- `K`: Minimum number of buildings to enclose
- `xi, yi`: Coordinates of the i-th building (1 ≤ xi, yi ≤ 10000)
- `wi`: Weight (cost) of the i-th building, can be negative

---

## 📤 Output Format

C
x1 y1 x2 y2
x2 y2 x3 y3
...
xn yn x1 y1

yaml
Copy
Edit

- `C`: Minimum cost (a floating-point number with **at least six digits** after the decimal)
- Each line after represents a polygon **edge** from `(xi, yi)` to `(xi+1, yi+1)`
- All edges must be **either vertical or horizontal**
- The polygon must be **closed** (last edge ends where the first started)

---

## ⚙️ Constraints

- The polygon must be **axis-aligned**
- The polygon must be **simple** and **closed**
- Coordinates can be floating points
- Buildings on the **boundary** are considered **enclosed**

---

## 💡 Sample Approach

### Step 1: Preprocessing
- Read the list of buildings
- Sort them based on `x` and `y` coordinates

### Step 2: Sliding Window or Brute Rectangles
- Try all rectangles formed by combinations of `x1, x2` and `y1, y2`
- For each rectangle:
  - Check how many buildings it encloses
  - If ≥ K, compute cost:
    ```
    Cost = 2 * ((x2 - x1) + (y2 - y1)) + sum(weights of enclosed buildings)
    ```

### Step 3: Optimization
- Try to reduce rectangle size while still enclosing ≥ K buildings
- Greedily consider rectangles enclosing buildings with more negative weights (more favorable)

### Step 4: Output
- Print the cost and four edges of the rectangle in order

---

## 📊 Complexity

- Time: Can be reduced to `O(N^2 log N)` with efficient sorting and sweeping
- Space: `O(N)` for storing building data

---

## ✅ Sample Output Format

12.000000
1.0 1.0 4.0 1.0
4.0 1.0 4.0 3.0
4.0 3.0 1.0 3.0
1.0 3.0 1.0 1.0

yaml
Copy
Edit

---

## 🚧 Implementation Note

- Be careful with **floating point precision**
- Optimize using **data structures** like segment trees or 2D prefix sums if needed
- Use **efficient pruning** to discard invalid rectangles early

---

## 🧪 Testing

- Try inputs with:
  - Some weights negative
  - All buildings aligned
  - All buildings scattered
  - K = 1, K = N

---
