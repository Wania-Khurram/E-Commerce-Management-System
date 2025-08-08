# 🛒 E-Commerce Management System

> A console-based **C++ OOP** project simulating an online marketplace with **Admins**, **Sellers**, and **Buyers**.

---

## 📌 Overview
The **E-Commerce Management System** is a **menu-driven console application** built in C++ using **Object-Oriented Programming (OOP)** principles.  
It allows **product management**, **cart operations**, and **order processing** with **file storage for persistence**.

The system demonstrates:
- 🏛 **Inheritance & Polymorphism**
- 🧩 **Composition & Aggregation**
- ➕ **Operator Overloading**
- ⚠ **Custom Exception Handling**
- 💾 **File I/O for Data Storage**

---

## 🚀 Features

### **👤 User Roles**
#### 🛡 Admin
- View all users
- View all orders
- Manage sellers and products (via file data)

#### 🏪 Seller
- Add products to sell
- View own products

#### 🛍 Buyer
- Browse available products
- Add/remove products in cart
- Checkout and place orders

---

### **📦 Product Categories**
- **Electronics** — Phones, Laptops, Tablets  
- **Clothing** — Shirts, Pants, Jackets  
- **Books** — Novels, Textbooks, Comics  

---

### **🛒 Shopping Cart**
- Add/Remove products with quantity  
- **Operator Overloading** (`+=` / `-=`) for cart updates  
- Automatic total price calculation  

---

### **📜 Order Processing**
- Generates a unique Order ID  
- Stores buyer details and purchased items  
- Saves order history to `orders.txt`  

---

### **💾 Data Persistence**
- Products loaded from `products.txt`  
- Orders saved to `orders.txt`  

---

## 🛠 Technologies Used
| Technology | Purpose |
|------------|---------|
| **C++** | Core logic |
| **OOP** | System design |
| **File I/O** | Data persistence |
| **Custom Exceptions** | Error handling |

---

## ▶️ How to Compile & Run

### **Compile**
```bash
g++ *.cpp -o ecommerce
./ecommerce

