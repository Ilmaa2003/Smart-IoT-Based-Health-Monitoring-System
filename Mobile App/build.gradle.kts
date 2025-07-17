// Top-level build file where you can add configuration options common to all sub-projects/modules.

plugins {
    alias(libs.plugins.android.application) apply false
    // Add other plugins if you have, e.g. Kotlin plugin:
}

buildscript {
    repositories {
        google()
        mavenCentral()
    }
    dependencies {
        // If you need classpath dependencies for legacy plugins (usually not needed with plugins DSL)
        // classpath("com.android.tools.build:gradle:VERSION")
        // classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:VERSION")
    }
}

allprojects {
    repositories {
        mavenCentral()
    }

}
