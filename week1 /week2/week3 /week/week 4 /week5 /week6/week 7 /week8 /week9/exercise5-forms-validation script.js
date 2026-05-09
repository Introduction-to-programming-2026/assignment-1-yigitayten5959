/**
 * Exercise 5: Forms & Validation
 * ================================
 * Add real-time validation and submit handling.
 */

const form = document.querySelector('#registration-form');
const successMsg = document.querySelector('#success-message');

// ============================================================
// HELPER: Show or clear an error on a field
// ============================================================
function showError(inputId, message) {
    const input = document.querySelector(`#${inputId}`);
    const errorSpan = document.querySelector(`#error-${inputId}`);
    
    input.classList.add('invalid');
    input.classList.remove('valid');
    errorSpan.textContent = message;
}

function clearError(inputId) {
    const input = document.querySelector(`#${inputId}`);
    const errorSpan = document.querySelector(`#error-${inputId}`);
    
    input.classList.remove('invalid');
    input.classList.add('valid');
    errorSpan.textContent = '';
}

// ============================================================
// TASK 2: Individual Field Validators
// ============================================================

function validateName() {
    const val = document.querySelector('#full-name').value.trim();
    if (val.length < 2) {
        showError('full-name', 'Name must be at least 2 characters.');
        return false;
    }
    clearError('full-name');
    return true;
}

function validateEmail() {
    const val = document.querySelector('#email').value.trim();
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailRegex.test(val)) {
        showError('email', 'Please enter a valid email address.');
        return false;
    }
    clearError('email');
    return true;
}

function validatePassword() {
    const val = document.querySelector('#password').value;
    const hasDigit = /\d/.test(val);
    
    if (val.length < 8 || !hasDigit) {
        showError('password', 'Password must be 8+ characters and contain a number.');
        updatePasswordStrength(val);
        return false;
    }
    clearError('password');
    updatePasswordStrength(val);
    return true;
}

function validateConfirmPassword() {
    const pass = document.querySelector('#password').value;
    const confirm = document.querySelector('#confirm-password').value;
    if (confirm !== pass || confirm === '') {
        showError('confirm-password', 'Passwords do not match.');
        return false;
    }
    clearError('confirm-password');
    return true;
}

function validateCountry() {
    const val = document.querySelector('#country').value;
    if (val === "") {
        showError('country', 'Please select your country.');
        return false;
    }
    clearError('country');
    return true;
}

function validateTerms() {
    const checkbox = document.querySelector('#terms');
    if (!checkbox.checked) {
        showError('terms', 'You must agree to the terms.');
        return false;
    }
    clearError('terms');
    return true;
}

// ============================================================
// TASK 4: Password Strength Indicator
// ============================================================
function updatePasswordStrength(password) {
    const strengthEl = document.querySelector('#password-strength');
    if (!strengthEl) return;

    let strength = 'Weak';
    let className = 'strength-weak';

    if (password.length >= 8 && /\d/.test(password) && /[A-Z]/.test(password)) {
        strength = 'Strong';
        className = 'strength-strong';
    } else if (password.length >= 6) {
        strength = 'Fair';
        className = 'strength-fair';
    }

    strengthEl.textContent = `Strength: ${strength}`;
    strengthEl.className = className;
}

// ============================================================
//
