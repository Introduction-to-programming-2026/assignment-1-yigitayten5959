/**
 * script.js — Final Project: Weather Dashboard
 * ============================================
 * Requirements implemented:
 * - const/let usage
 * - async/await with try/catch
 * - localStorage persistence
 * - Modular functions
 * - Custom UI notifications (no alerts)
 */

// --- Constants & Selectors ---
const API_KEY = 'YOUR_OPENWEATHER_API_KEY'; // You would get this from openweathermap.org
const searchForm = document.querySelector('#search-form');
const cityInput = document.querySelector('#city-input');
const weatherDisplay = document.querySelector('#weather-display');
const historyList = document.querySelector('#history-list');

// --- Initialization ---
let searchHistory = JSON.parse(localStorage.getItem('weatherHistory')) || [];

/**
 * TASK 1: Fetch Weather Data (Async/Await)
 */
async function getWeatherData(city) {
    const url = `https://api.openweathermap.org/data/2.5/weather?q=${city}&units=metric&appid=${API_KEY}`;
    
    showLoading();

    try {
        const response = await fetch(url);
        
        if (!response.ok) {
            throw new Error(response.status === 404 ? 'City not found' : 'Network error');
        }

        const data = await response.json();
        updateUI(data);
        addToHistory(data.name);

    } catch (error) {
        handleUIError(error.message);
    }
}

/**
 * TASK 2: Update the User Interface
 */
function updateUI(data) {
    weatherDisplay.innerHTML = `
        <div class="weather-card">
            <h2>${data.name}, ${data.sys.country}</h2>
            <div class="temp">${Math.round(data.main.temp)}°C</div>
            <p class="condition">${data.weather[0].description}</p>
            <div class="details">
                <span>Humidity: ${data.main.humidity}%</span>
                <span>Wind: ${data.wind.speed} m/s</span>
            </div>
        </div>
    `;
}

/**
 * TASK 3: Manage LocalStorage Persistence
 */
function addToHistory(city) {
    if (!searchHistory.includes(city)) {
        searchHistory.push(city);
        // Limit history to last 5 items
        if (searchHistory.length > 5) searchHistory.shift();
        
        localStorage.setItem('weatherHistory', JSON.stringify(searchHistory));
        renderHistory();
    }
}

function renderHistory() {
    if (!historyList) return;
    historyList.innerHTML = searchHistory
        .map(city => `<button class="history-btn">${city}</button>`)
        .join('');
}

/**
 * TASK 4: Error & Loading Handlers (No Alerts)
 */
function showLoading() {
    weatherDisplay.innerHTML = '<div class="loader">Loading weather data...</div>';
}

function handleUIError(message) {
    weatherDisplay.innerHTML = `
        <div class="error-container">
            <p>⚠️ Error: ${message}</p>
            <p>Please check the spelling or your API key.</p>
        </div>
    `;
}

// --- Event Listeners ---
searchForm?.addEventListener('submit', (e) => {
    e.preventDefault();
    const city = cityInput.value.trim();
    if (city) {
        getWeatherData(city);
        cityInput.value = '';
    }
});

// Re-fetch from history clicks
historyList?.addEventListener('click', (e) => {
    if (e.target.classList.contains('history-btn')) {
        getWeatherData(e.target.textContent);
    }
});

// Startup
console.log('Final project script loaded. Time to build something great! 🚀');
renderHistory();
