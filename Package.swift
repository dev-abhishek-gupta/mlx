// swift-tools-version:5.9

import PackageDescription

let package = Package(
    name: "mlx",
    platforms: [
        .macOS(.v14)
    ],
    products: [
        .library(name: "MLX", targets: ["MLX"]),
        .library(name: "MLXNN", targets: ["MLXNN"]),
        .library(name: "MLXOptimizers", targets: ["MLXOptimizers"]),
        .library(name: "MLXData", targets: ["MLXData"]),
        .library(name: "MLXLMCommon", targets: ["MLXLMCommon"]),
    ],
    dependencies: [],
    targets: [
        .target(
            name: "MLX",
            path: "Sources/mlx"
        ),
        .target(
            name: "MLXNN",
            dependencies: ["MLX"],
            path: "Sources/mlx-nn"
        ),
        .target(
            name: "MLXOptimizers",
            dependencies: ["MLX"],
            path: "Sources/mlx-optimizers"
        ),
        .target(
            name: "MLXData",
            dependencies: ["MLX"],
            path: "Sources/mlx-data"
        ),
        .target(
            name: "MLXLMCommon",
            dependencies: ["MLX", "MLXNN", "MLXOptimizers"],
            path: "Sources/MLXLMCommon"
        )
    ]
)

