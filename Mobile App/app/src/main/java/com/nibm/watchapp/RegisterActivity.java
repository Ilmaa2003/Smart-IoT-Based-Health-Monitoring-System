package com.nibm.watchapp;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;

public class RegisterActivity extends AppCompatActivity {

    private TextInputEditText edtFullName, edtEmail, edtPassword, edtConfirmPassword;
    private Button btnRegister;
    private TextView tvLogin;
    private DatabaseHelper dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        edtFullName = findViewById(R.id.edtFullName);
        edtEmail = findViewById(R.id.edtEmail);
        edtPassword = findViewById(R.id.edtPassword);
        edtConfirmPassword = findViewById(R.id.edtConfirmPassword);
        btnRegister = findViewById(R.id.btnRegister);
        tvLogin = findViewById(R.id.tvAlreadyHaveAccount); // FIX: Initialization added

        dbHelper = new DatabaseHelper(this);

        btnRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String fullName = edtFullName.getText() != null ? edtFullName.getText().toString().trim() : "";
                String email = edtEmail.getText() != null ? edtEmail.getText().toString().trim() : "";
                String password = edtPassword.getText() != null ? edtPassword.getText().toString() : "";
                String confirmPassword = edtConfirmPassword.getText() != null ? edtConfirmPassword.getText().toString() : "";

                if (validateInputs(fullName, email, password, confirmPassword)) {
                    // Register with full name too (ensure your DB supports this)
                    boolean success = dbHelper.registerUser(fullName, email, password);
                    if (success) {
                        Toast.makeText(RegisterActivity.this, "Registration successful!", Toast.LENGTH_SHORT).show();

                        // Optional: Clear inputs
                        edtFullName.setText("");
                        edtEmail.setText("");
                        edtPassword.setText("");
                        edtConfirmPassword.setText("");

                        finish(); // Return to login screen
                    } else {
                        Toast.makeText(RegisterActivity.this, "Registration failed! User may already exist.", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });

        tvLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(RegisterActivity.this, LoginActivity.class);
                startActivity(intent);
            }
        });
    }

    private boolean validateInputs(String fullName, String email, String password, String confirmPassword) {
        boolean isValid = true;

        // Full Name
        if (TextUtils.isEmpty(fullName)) {
            edtFullName.setError("Full name is required");
            edtFullName.requestFocus();
            isValid = false;
        } else if (fullName.length() < 2) {
            edtFullName.setError("Full name is too short");
            edtFullName.requestFocus();
            isValid = false;
        } else {
            edtFullName.setError(null);
        }

        // Email
        if (TextUtils.isEmpty(email)) {
            edtEmail.setError("Email is required");
            if (isValid) edtEmail.requestFocus();
            isValid = false;
        } else if (!Patterns.EMAIL_ADDRESS.matcher(email).matches()) {
            edtEmail.setError("Invalid email format");
            if (isValid) edtEmail.requestFocus();
            isValid = false;
        } else {
            edtEmail.setError(null);
        }

        // Password
        if (TextUtils.isEmpty(password)) {
            edtPassword.setError("Password is required");
            if (isValid) edtPassword.requestFocus();
            isValid = false;
        } else if (password.length() < 6) {
            edtPassword.setError("Password must be at least 6 characters");
            if (isValid) edtPassword.requestFocus();
            isValid = false;
        } else {
            edtPassword.setError(null);
        }

        // Confirm Password
        if (TextUtils.isEmpty(confirmPassword)) {
            edtConfirmPassword.setError("Please confirm your password");
            if (isValid) edtConfirmPassword.requestFocus();
            isValid = false;
        } else if (!password.equals(confirmPassword)) {
            edtConfirmPassword.setError("Passwords do not match");
            if (isValid) edtConfirmPassword.requestFocus();
            isValid = false;
        } else {
            edtConfirmPassword.setError(null);
        }

        return isValid;
    }
}
