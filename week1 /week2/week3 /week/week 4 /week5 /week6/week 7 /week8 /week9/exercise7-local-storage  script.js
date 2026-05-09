/**
 * Exercise 7: Local Storage — Notes App
 * =======================================
 * Build a full CRUD notes app using localStorage.
 */

// ============================================================
// TASK 1 — Initialize: Load notes from localStorage
// ============================================================

const STORAGE_KEY = 'week9_notes';

// Load existing notes or start with an empty array
let notes = JSON.parse(localStorage.getItem(STORAGE_KEY)) || [];
let editingId = null; // null means "add" mode, a number means "edit" mode

function saveNotes() {
    // Save notes array as a JSON string to the browser's storage
    localStorage.setItem(STORAGE_KEY, JSON.stringify(notes));
}

// ============================================================
// TASK 3 — Render Notes
// ============================================================

const notesContainer = document.querySelector('#notes-container');
const notesCount = document.querySelector('#notes-count');

function renderNotes(filter = '') {
    notesContainer.innerHTML = '';

    // 1. Filter notes by search term
    let filtered = notes.filter(n => 
        n.title.toLowerCase().includes(filter.toLowerCase()) || 
        n.body.toLowerCase().includes(filter.toLowerCase())
    );

    // 2. Sort so pinned notes appear first
    filtered.sort((a, b) => b.pinned - a.pinned || b.createdAt - a.createdAt);

    // Update count display
    if(notesCount) notesCount.textContent = `${filtered.length} notes found`;

    if (filtered.length === 0) {
        notesContainer.innerHTML = `
            <div class="empty-state">
                <p>${filter ? `No results for "${filter}"` : 'No notes yet. Create your first one!'}</p>
            </div>`;
        return;
    }

    // 3. Create Note Cards
    filtered.forEach(note => {
        const date = new Date(note.createdAt).toLocaleDateString('en-US', {
            month: 'short', day: 'numeric', year: 'numeric'
        });

        const bodyPreview = note.body.length > 100 
            ? note.body.substring(0, 100) + '...' 
            : note.body;

        const card = document.createElement('div');
        card.className = `note-card ${note.pinned ? 'pinned' : ''}`;
        card.innerHTML = `
            <div class="note-header">
                <h3>${note.pinned ? '📌 ' : ''}${note.title}</h3>
                <div class="note-actions">
                    <button data-id="${note.id}" data-action="pin" title="Pin Note">📍</button>
                    <button data-id="${note.id}" data-action="edit" title="Edit Note">✏️</button>
                    <button data-id="${note.id}" data-action="delete" title="Delete Note">🗑️</button>
                </div>
            </div>
            <p>${bodyPreview}</p>
            <div class="note-footer">
                <small>${date}</small>
            </div>
        `;
        notesContainer.appendChild(card);
    });
}

// ============================================================
// TASK 2 & 4 — Create & Update Notes
// ============================================================

const noteForm   = document.querySelector('#note-form');
const titleInput = document.querySelector('#note-title');
const bodyInput  = document.querySelector('#note-body');
const submitBtn  = document.querySelector('#btn-submit');
const cancelBtn  = document.querySelector('#btn-cancel');
const formTitle  = document.querySelector('#form-title');

noteForm.addEventListener('submit', function(event) {
    event.preventDefault();

    const title = titleInput.value.trim();
    const body  = bodyInput.value.trim();

    if (!title) { titleInput.focus(); return; }

    if (editingId !== null) {
        // UPDATE existing note
        notes = notes.map(n => n.id === editingId ? { ...n, title, body } : n);
        resetForm();
    } else {
        // CREATE new note
        const newNote = {
            id: Date.now(), // Unique timestamp as ID
            title,
            body,
            createdAt: Date.now(),
            pinned: false
        };
        notes.unshift(newNote);
    }

    saveNotes();
    renderNotes();
    noteForm.reset();
});

function resetForm() {
    editingId = null;
    formTitle.textContent = "New Note";
    submitBtn.textContent = "💾 Save Note";
    cancelBtn.classList.add('hidden');
    noteForm.reset();
}

cancelBtn.addEventListener('click', resetForm);

// ============================================================
// TASKS 4 & 5 — Edit, Pin, Delete via Event Delegation
// ============================================================

notesContainer.addEventListener('click', function(event) {
    const btn = event.target.closest('button[data-action]');
    if (!btn) return;

    const id = parseInt(btn.dataset.id);
    const action = btn.dataset.action;

    if (action === 'delete') {
        if (confirm('Delete this note permanently?')) {
            notes = notes.filter(n => n.id !== id);
            saveNotes();
            renderNotes();
        }
    }

    if (action === 'pin') {
        notes = notes.map(n => n.id === id ? { ...n, pinned: !n.pinned } : n);
        saveNotes();
        renderNotes();
    }

    if (action === 'edit') {
        const note = notes.find(n => n.id === id);
        if (note) {
            editingId = id;
            titleInput.value = note.title;
            bodyInput.value = note.body;
            formTitle.textContent = "Edit Note";
            submitBtn.textContent = "✅ Update Note";
            cancelBtn.classList.remove('hidden');
            window.scrollTo({ top: 0, behavior: 'smooth' });
            titleInput.focus();
        }
    }
});

// ============================================================
// TASK 6 — Search Filter
// ============================================================

const searchInput = document.querySelector('#search-input');
searchInput.addEventListener('input', () => {
    renderNotes(searchInput.value);
