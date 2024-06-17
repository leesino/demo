package com.example.compose.sample


import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.layout.Column
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.OutlinedButton
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp


@Composable
fun ButtonSample() {
    Column {
        Button(onClick = {}) {
            Text(text = "简单按钮")  }
        Button(onClick = {}, enabled = false) {
            Text(text = "被禁用的按钮") }
        Button(onClick = {},
            border = BorderStroke(1.dp, Color.Red)
        ) {
            Text(text = "带边框的按钮")  }
        Button(onClick = {},
            colors = ButtonDefaults.buttonColors(
                containerColor = Color.Yellow,
                contentColor = Color.Green,
                disabledContainerColor = Color.Gray,
                disabledContentColor = Color.Black
            )
        ) {
            Text(text = "自定义颜色的按钮")  }
    }
}

@Composable
fun ButtonSample1(){
    Column {
        TextButton(
            onClick = { },
        ) {
            Text(text = "TextButton")
        }

        OutlinedButton(
            onClick = { },
        ) {
            Text(text = "OutlinedButton")
        }

        IconButton( onClick = {}, ) {
            Icon(imageVector = Icons.Default.ArrowBack,
                contentDescription = null)
        }
    }
}

@Preview
@Composable
fun ButtonSamplePreview() {
    ButtonSample()
}
