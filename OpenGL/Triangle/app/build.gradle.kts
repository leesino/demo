plugins {
    id("com.android.application")
}

android {
    namespace = "com.example.opengl.triangle"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.opengl.triangle"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"


        externalNativeBuild {
            cmake {
                cppFlags += "-std=c++17"
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }

}

dependencies {


}