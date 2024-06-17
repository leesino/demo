package com.example.compose.sample


import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.absolutePadding
import androidx.compose.foundation.layout.offset
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp


@Composable
fun ModifierSample1() {
    Column {
        Text(text = "大小",
            modifier = Modifier.size(30.dp))
        Text(text = "大小",
            modifier = Modifier.size(width = 30.dp, height = 20.dp))
    }
}

@Composable
fun ModifierSample2() {
    Column {
        Text(text = "背景颜色及形状",
            modifier = Modifier.background(
                color = Color.Red,
                shape = RoundedCornerShape(5.dp)
            )
        )
        Text(text = "背景渐变色",
            modifier = Modifier.background(
                brush = Brush.horizontalGradient(
                    listOf(Color.Green, Color.Blue)
                )
            )
        )
    }
}

@Composable
fun ModifierSample3() {
    Column (modifier = Modifier.background(color = Color.Gray)){
        Text(text = "内边距",
            modifier = Modifier
                .background(color = Color.Red)
                .padding(10.dp)
        )
        Text(text = "内边距",
            modifier = Modifier
                .padding(horizontal = 10.dp, vertical = 10.dp)
                .background(color = Color.Yellow)
        )
    }
}

@Composable
fun ModifierSample4() {
    Column {

        Text(text = "边框框",
            modifier = Modifier
                .padding(10.dp)
        )
        Text(text = "内边距",
            modifier = Modifier
                .padding(10.dp)
        )

    }
}

@Preview
@Composable
fun ModifierSamplePreview() {
    ModifierSample4()
}
