const express = require("express");
const cors = require("cors");

const fs = require("fs");
const path = require("path");
const { execFile } = require("child_process");
const os = require("os");

const app = express();

const frontendPath =
    path.join(
        __dirname,
        "../frontend/dist"
    );

app.use(
    express.static(
        frontendPath
    )
);

app.use(cors());

app.use(
    express.json({
        limit: "1mb"
    })
);


app.post(
    "/compile",
    (req, res) =>
    {
        const code = req.body.code;

        if (
            typeof code !== "string"
        )
        {
            return res.status(400).json({
                success: false,
                output:
                    "Error: No source code received."
            });
        }


        /*
         * Create a unique temporary file.
         */
        const filename =
            path.join(
                os.tmpdir(),
                `p0_${Date.now()}.p0`
            );


        fs.writeFileSync(
            filename,
            code
        );


        /*
         * Path to your existing compiler.
         *
         * web-backend/ is inside p0/,
         * so ../compiler points to:
         *
         * p0/compiler
         */
        const compilerPath =
            path.join(
                __dirname,
                "../compiler"
            );


        execFile(
            compilerPath,
            [filename],
            {
                timeout: 5000
            },
            (
                error,
                stdout,
                stderr
            ) =>
            {
                /*
                 * Remove temporary source file.
                 */
                fs.unlink(
                    filename,
                    () => {}
                );


                let output = "";

                if (stdout)
                {
                    output += stdout;
                }

                if (stderr)
                {
                    output += stderr;
                }


                if (error)
                {
                    if (!output)
                    {
                        output =
                            error.message;
                    }

                    return res.json({
                        success: false,
                        output: output
                    });
                }


                res.json({
                    success: true,
                    output:
                        output ||
                        "Compilation finished successfully."
                });
            }
        );
    }
);


// app.listen(
//     3001,
//     () =>
//     {
//         console.log(
//             "P0 backend running on http://localhost:3001"
//         );
//     }
// );

app.get(
    "/{*splat}",
    (req, res) =>
    {
        res.sendFile(
            path.join(
                frontendPath,
                "index.html"
            )
        );
    }
);

const PORT =
    process.env.PORT || 3001;


app.listen(
    PORT,
    () => {
        console.log(
            `Compiler server running on port ${PORT}`
        );
    }
);