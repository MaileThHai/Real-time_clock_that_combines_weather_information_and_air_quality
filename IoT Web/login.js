const loginForm = document.getElementById('login-form');
const errorMessage = document.getElementById('error-message');
const eyeIcon = document.getElementById('eye-icon');
const passwordInput = document.getElementById('password');

loginForm.addEventListener('submit', function(event) {
  event.preventDefault();

  const username = document.getElementById('username').value;
  const password = passwordInput.value;

  // Kiểm tra thông tin đăng nhập
  if (username === 'admin' && password === 'admin') {
    // Đăng nhập thành công, chuyển hướng đến trang khác
    window.location.href = 'Layout.html';
  } else {
    // Hiển thị thông báo lỗi
    errorMessage.innerText = 'Tên đăng nhập hoặc mật khẩu không chính xác.';
  }
});

// Hiển thị mật khẩu khi nhấn vào biểu tượng con mắt
eyeIcon.addEventListener('click', function() {
  if (passwordInput.type === 'password') {
    passwordInput.type = 'text';
    eyeIcon.classList.remove('fa-eye');
    eyeIcon.classList.add('fa-eye-slash');
  } else {
    passwordInput.type = 'password';
    eyeIcon.classList.remove('fa-eye-slash');
    eyeIcon.classList.add('fa-eye');
  }
});
