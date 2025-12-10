function showError(input, message) {
    const formControl = input.parentElement;
    const errorDisplay = formControl.querySelector('.error');
    
    if (!errorDisplay) {
        const errorElement = document.createElement('small');
        errorElement.className = 'error';
        errorElement.textContent = message;
        formControl.appendChild(errorElement);
    } else {
        errorDisplay.textContent = message;
    }
    
    input.classList.add('error-border');
}

function clearError(input) {
    const formControl = input.parentElement;
    const errorDisplay = formControl.querySelector('.error');
    
    if (errorDisplay) {
        formControl.removeChild(errorDisplay);
    }
    
    input.classList.remove('error-border');
}

function validateEmail(email) {
    const re = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return re.test(String(email).toLowerCase());
}

//==================================================================================
// Sign Up Validation
function validateSignUp() {
    let isValid = true;
    
    const username = document.getElementById('username');
    const password = document.getElementById('password');
    const confirmPassword = document.getElementById('confirm-password');
    const email = document.getElementById('email');
    
    
    clearError(username);
    clearError(password);
    clearError(confirmPassword);
    clearError(email);
    
    //-----------------------------------------------------------------------------
    // Validate username
    if (username.value.trim().length < 3) {
        showError(username, 'Username must be at least 3 characters');
        alert('Username must be at least 3 characters');
        isValid = false;
    }
    //-----------------------------------------------------------------------------
    // Validate password
    if (password.value.length < 3) {
        showError(password, 'Password must be at least 3 characters');
        alert('Password must be at least 3 characters');
        isValid = false;
    }
    //-----------------------------------------------------------------------------
    // Validate confirm password
    if (confirmPassword.value !== password.value) {
        showError(confirmPassword, 'Passwords do not match');
        alert('Passwords do not match');
        isValid = false;
    }
    //----------------------------------------------------------------------------
    // Validate email
    if (!validateEmail(email.value)) {
        showError(email, 'Please enter a valid email address');
        alert('Please enter a valid email address')
        isValid = false;
    }
    
    if (isValid) {
        const user = {
            username: username.value,
            password: password.value,
            email: email.value,
            isAdmin: document.getElementById('is-admin').checked
        };
        
        localStorage.setItem('currentUser', JSON.stringify(user));
        
        let users = JSON.parse(localStorage.getItem('users')) || [];
        users.push(user);
        localStorage.setItem('users', JSON.stringify(users));
        window.location.href = 'login.html';
    }
    
    return false;
}

//===============================================================================
// Login Validation
function validateLogin() {
    let isValid = true;
    
    const username = document.getElementById('username');
    const password = document.getElementById('password');
    
    clearError(username);
    clearError(password);
    
    //-----------------------------------------------------------------------------
    // Validate username
    if (username.value.trim().length < 3) {
        showError(username, 'Username must be at least 3 characters');
        isValid = false;
    }
    //-----------------------------------------------------------------------------
    // Validate password
    if (password.value.length < 3) {
        showError(password, 'Password must be at least 3 characters');
        isValid = false;
    }
    
    
    if (isValid) {
        const users = JSON.parse(localStorage.getItem('users')) || [];
        const user = users.find(u => u.username === username.value && u.password === password.value);
        
        if (!user) {
            showError(username, 'Invalid username or password');
            showError(password, 'Invalid username or password');
            alert('Invalid username or password');
            isValid = false;
        } else {
            localStorage.setItem('currentUser', JSON.stringify(user));
            window.location.href = 'recipes_list.html';
        }
    }
    
    return false;
}

//===================================================================================================
document.addEventListener('DOMContentLoaded', function() {
    const signUpForm = document.getElementById('signup-form');
    if (signUpForm) {
        signUpForm.onsubmit = validateSignUp;
    }
    
    const loginForm = document.getElementById('login-form');
    if (loginForm) {
        loginForm.onsubmit = validateLogin;
    }
});