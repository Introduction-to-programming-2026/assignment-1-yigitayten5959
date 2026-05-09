/**
 * Exercise 6: Fetch & APIs
 * =========================
 * Complete each async function below.
 * All APIs used are free and require no authentication.
 */

// ============================================================
// UTILITY: Show a loading spinner inside an element
// ============================================================
function showLoading(element) {
  element.innerHTML = '<div class="spinner"></div>';
}

function showError(element, message) {
  element.innerHTML = `<p class="error-text">❌ ${message}</p>`;
}


// ============================================================
// TASK 1 — Random Quote
// API: https://api.quotable.io/random
// ============================================================
const quoteDisplay = document.querySelector('#quote-display');
const btnNewQuote  = document.querySelector('#btn-new-quote');

async function fetchQuote() {
  showLoading(quoteDisplay);

  try {
    const response = await fetch('https://api.quotable.io/random');
    
    if (!response.ok) {
        throw new Error('Failed to fetch quote');
    }

    const data = await response.json();
    
    quoteDisplay.innerHTML = `
      <blockquote>"${data.content}"</blockquote>
      <p class="quote-author">— ${data.author}</p>
    `;

  } catch (error) {
    showError(quoteDisplay, 'Could not load quote. Check your connection.');
    console.error(error);
  }
}

// Fetch a quote when the page loads, and on button click
fetchQuote();
btnNewQuote.addEventListener('click', fetchQuote);


// ============================================================
// TASK 2 — GitHub User Search
// API: https://api.github.com/users/{username}
// ============================================================
const githubInput  = document.querySelector('#github-input');
const btnSearch    = document.querySelector('#btn-search-user');
const githubResult = document.querySelector('#github-result');

async function searchUser() {
  const username = githubInput.value.trim();
  if (!username) return;

  showLoading(githubResult);

  try {
    const response = await fetch(`https://api.github.com/users/${username}`);
    
    if (response.status === 404) {
        githubResult.innerHTML = '<p class="error-text">🔍 User not found</p>';
        return;
    }
    
    if (!response.ok) throw new Error('Search failed');

    const user = await response.json();
    
    githubResult.innerHTML = `
      <div class="github-card">
        <img src="${user.avatar_url}" alt="${user.login}" class="avatar">
        <h3>${user.name || user.login}</h3>
        <p class="bio">${user.bio || 'This user has no bio.'}</p>
        <div class="stats">
            <span><strong>Followers:</strong> ${user.followers}</span>
            <span><strong>Repos:</strong> ${user.public_repos}</span>
        </div>
        <a href="${user.html_url}" target="_blank" class="profile-link">View GitHub Profile</a>
      </div>
    `;

  } catch (error) {
    showError(githubResult, error.message || 'Search failed. Try again.');
  }
}

btnSearch.addEventListener('click', searchUser);
githubInput.addEventListener('keydown', (e) => { if (e.key === 'Enter') searchUser(); });


// ============================================================
// TASK 3 — Posts Feed with Pagination
// API: https://jsonplaceholder.typicode.com/posts
// ============================================================
const postsContainer = document.querySelector('#posts-container');
const btnLoadMore    = document.querySelector('#btn-load-more');
let currentPage = 1;
const postsPerPage = 5;

async function loadPosts() {
  const start = (currentPage - 1) * postsPerPage;
  
  try {
    const response = await fetch(`https://jsonplaceholder.typicode.com/posts?_start=${start}&_limit=${postsPerPage}`);
    const posts = await response.json();

    posts.forEach(post => {
        const card = document.createElement('div');
        card.className = 'post-card';
        card.innerHTML = `
            <h4>${post.title}</h4>
            <p>${post.body.substring(0, 100)}...</p>
            <button class="comment-toggle">Show Comments</button>
            <div class="comments-section hidden"></div>
        `;
        
        // Load comments logic
        const toggleBtn =
