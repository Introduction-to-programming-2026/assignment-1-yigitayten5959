/**
 * Exercise 4: JavaScript & the DOM
 * ==================================
 * Complete each task below. Read the README.md for full instructions.
 * Open the browser console (F12) to debug.
 */

// ============================================================
// TASK 1 — Console Warmup
// ============================================================

// TODO 1a: Select the element with id "main-title" and change its text
document.getElementById('main-title').textContent = "DOM Mastery 🚀";

// TODO 1b: Select ALL elements with class "card", log how many there are
const cards = document.querySelectorAll('.card');
console.log(`Total cards found: ${cards.length}`);

// TODO 1c: Select the element with id "target-box" and change its background
const targetBox = document.getElementById('target-box');
targetBox.style.backgroundColor = "#6c5ce7";
targetBox.style.color = "white";


// ============================================================
// TASK 2 — Click Counter
// ============================================================

const countDisplay = document.querySelector('#count-display');
const btnDec = document.querySelector('#btn-decrement');
const btnReset = document.querySelector('#btn-reset');
const btnInc = document.querySelector('#btn-increment');

let count = 0;

function updateCountDisplay() {
    countDisplay.textContent = count;
    
    // Class management for visual feedback
    if (count === 0) {
        countDisplay.classList.add('zero');
        countDisplay.classList.remove('high');
    } else if (count > 5) {
        countDisplay.classList.add('high');
        countDisplay.classList.remove('zero');
    } else {
        countDisplay.classList.remove('zero', 'high');
    }
}

btnInc.addEventListener('click', () => {
    count++;
    updateCountDisplay();
});

btnDec.addEventListener('click', () => {
    if (count > 0) { // Preventing negative numbers
        count--;
        updateCountDisplay();
    }
});

btnReset.addEventListener('click', () => {
    count = 0;
    updateCountDisplay();
});

updateCountDisplay();


// ============================================================
// TASK 3 — Dynamic List Builder
// ============================================================

const listInput = document.querySelector('#list-input');
const addItemBtn = document.querySelector('#btn-add-item');
const dynamicList = document.querySelector('#dynamic-list');

addItemBtn.addEventListener('click', () => {
    const text = listInput.value.trim();
    
    if (text === "") {
        alert("Please enter some text!");
        return;
    }

    // Create <li> and × delete button
    const li = document.createElement('li');
    li.innerHTML = `${text} <button class="delete-btn">×</button>`;
    
    dynamicList.appendChild(li);
    
    // Reset input
    listInput.value = "";
    listInput.focus();
});

// Event Delegation for delete buttons
dynamicList.addEventListener('click', function(event) {
    if (event.target.classList.contains('delete-btn')) {
        event.target.parentElement.remove();
    }
});


// ============================================================
// TASK 4 — Show / Hide Toggle
// ============================================================

const toggleBtn = document.querySelector('#btn-toggle');
const detailsDiv = document.querySelector('.details');

toggleBtn.addEventListener('click', () => {
    const isHidden = detailsDiv.classList.toggle('hidden');
    toggleBtn.textContent = isHidden ? "Show Details" : "Hide Details";
});


// ============================================================
// TASK 5 — Color Mixer
// ============================================================

const sliderR = document.querySelector('#slider-r');
const sliderG = document.querySelector('#slider-g');
const sliderB = document.querySelector('#slider-b');
const colorPreview = document.querySelector('#color-preview');
const hexDisplay = document.querySelector('#hex-
