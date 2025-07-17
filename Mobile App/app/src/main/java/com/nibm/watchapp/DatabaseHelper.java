package com.nibm.watchapp;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DatabaseHelper extends SQLiteOpenHelper {

    private static final String DATABASE_NAME = "OrbitLife.db";
    private static final int DATABASE_VERSION = 1;

    public static final String TABLE_USERS = "users";
    public static final String COL_EMAIL = "email";
    public static final String COL_PASSWORD = "password";
    public static final String COL_NAME = "full_name"; // ✅ New column for name

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        // ✅ Create users table with full_name
        String CREATE_USERS_TABLE = "CREATE TABLE " + TABLE_USERS + " (" +
                COL_EMAIL + " TEXT PRIMARY KEY, " +
                COL_NAME + " TEXT, " +
                COL_PASSWORD + " TEXT)";
        db.execSQL(CREATE_USERS_TABLE);

        // ✅ Insert sample user (optional)
        ContentValues values = new ContentValues();
        values.put(COL_EMAIL, "test@example.com");
        values.put(COL_NAME, "Test User");
        values.put(COL_PASSWORD, "123456");
        db.insert(TABLE_USERS, null, values);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_USERS);
        onCreate(db);
    }

    // ✅ Check login credentials
    public boolean checkUserCredentials(String email, String password) {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT * FROM " + TABLE_USERS + " WHERE " +
                COL_EMAIL + "=? AND " + COL_PASSWORD + "=?", new String[]{email, password});
        boolean exists = (cursor.getCount() > 0);
        cursor.close();
        db.close();
        return exists;
    }

    // ✅ Register user with name
    public boolean registerUser(String fullName, String email, String password) {
        SQLiteDatabase db = this.getWritableDatabase();

        // Check if user already exists
        Cursor cursor = db.rawQuery("SELECT * FROM " + TABLE_USERS + " WHERE " + COL_EMAIL + " = ?", new String[]{email});
        if (cursor.getCount() > 0) {
            cursor.close();
            return false; // User already exists
        }
        cursor.close();

        // Insert new user with name
        ContentValues values = new ContentValues();
        values.put(COL_EMAIL, email);
        values.put(COL_NAME, fullName);
        values.put(COL_PASSWORD, password); // 🔐 Remember to hash this in production

        long result = db.insert(TABLE_USERS, null, values);
        return result != -1;
    }

    // ✅ Optional: Get full name by email
    public String getFullNameByEmail(String email) {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT " + COL_NAME + " FROM " + TABLE_USERS + " WHERE " + COL_EMAIL + " = ?", new String[]{email});
        String name = null;
        if (cursor.moveToFirst()) {
            name = cursor.getString(cursor.getColumnIndexOrThrow(COL_NAME));
        }
        cursor.close();
        db.close();
        return name;
    }
}
