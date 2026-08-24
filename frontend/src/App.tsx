// // import { useState } from "react";
// // import Editor from "@monaco-editor/react";

// // import "./App.css";

// // function App() {
// //     const [code, setCode] = useState("");
// //     const [output, setOutput] = useState<string[]>([
// //         "Welcome to <prototype 0> IDE"
// //     ]);

// //     // function compileCode() {
// //     //     setOutput([
// //     //         "Compiling...",
// //     //         "Compiler backend not connected yet."
// //     //     ]);
// //     // }

// //     async function compileCode() {
// //         setOutput([
// //             "Compiling..."
// //         ]);

// //         try {
// //             const response =
// //                 await fetch(
// //                     "http://localhost:3001/compile",
// //                     {
// //                         method: "POST",

// //                         headers: {
// //                             "Content-Type":
// //                                 "application/json"
// //                         },

// //                         body:
// //                             JSON.stringify({
// //                                 code: code
// //                             })
// //                     }
// //                 );

// //             const result =
// //                 await response.json();


// //             const lines =
// //                 result.output
// //                     .split("\n")
// //                     .filter(
// //                         (line: string) =>
// //                             line.trim() !== ""
// //                     );


// //             setOutput(
// //                 lines.length > 0
// //                     ? lines
// //                     : [
// //                         result.success
// //                             ? "Compilation finished successfully."
// //                             : "Compilation failed."
// //                     ]
// //             );
// //         }
// //         catch (error) {
// //             setOutput([
// //                 "Error: Could not connect to compiler backend.",
// //                 "Make sure server.js is running on port 3001."
// //             ]);
// //         }
// //     }

    
// //     function runCode() {
// //         setOutput([
// //             "Running...",
// //             "Interpreter backend not connected yet."
// //         ]);
// //     }

// //     function saveFile() {
// //         const blob = new Blob(
// //             [code],
// //             {
// //                 type: "text/plain"
// //             }
// //         );

// //         const url =
// //             URL.createObjectURL(blob);

// //         const link =
// //             document.createElement("a");

// //         link.href = url;

// //         link.download =
// //             "source_code.p0";

// //         link.click();

// //         URL.revokeObjectURL(url);

// //         setOutput([
// //             "File saved as source_code.p0"
// //         ]);
// //     }

// //     return (
// //         <div className="ide">

// //             <header className="ide-header">
// //                 <h1>&lt;prototype 0&gt; IDE</h1>
// //             </header>

// //             <nav className="menu-bar">

// //                 <button>
// //                     File
// //                 </button>

// //                 <button>
// //                     Edit
// //                 </button>

// //                 <button
// //                     onClick={compileCode}
// //                 >
// //                     Compile
// //                 </button>

// //                 <button
// //                     onClick={runCode}
// //                 >
// //                     Run
// //                 </button>

// //                 <button
// //                     className="save-button"
// //                     onClick={saveFile}
// //                 >
// //                     Save
// //                 </button>

// //             </nav>

// //             <div className="file-bar">
// //                 source_code.p0
// //             </div>

// //             <main className="editor-container">

// //                 <Editor
// //                     height="100%"
// //                     defaultLanguage="plaintext"
// //                     value={code}
// //                     onChange={(value) =>
// //                         setCode(value || "")
// //                     }
// //                     theme="vs-dark"
// //                     options={{
// //                         fontSize: 16,
// //                         fontFamily:
// //                             "'Courier New', monospace",

// //                         lineNumbers: "on",

// //                         minimap: {
// //                             enabled: false
// //                         },

// //                         scrollBeyondLastLine: false,

// //                         automaticLayout: true,

// //                         cursorBlinking: "blink",

// //                         cursorStyle: "line",

// //                         padding: {
// //                             top: 10
// //                         }
// //                     }}
// //                 />

// //             </main>

// //             <section className="output-panel">

// //                 <div className="output-title">
// //                     Messages / Output
// //                 </div>

// //                 <div className="output-content">

// //                     {output.map(
// //                         (message, index) => (
// //                             <div
// //                                 key={index}
// //                                 className="output-line"
// //                             >
// //                                 {message}
// //                             </div>
// //                         )
// //                     )}

// //                 </div>

// //             </section>

// //             <footer className="status-bar">

// //                 Ctrl+S Save |
// //                 F9 Compile |
// //                 Ctrl+R Run

// //             </footer>

// //         </div>
// //     );
// // }

// // export default App;

// import { useState } from "react";
// import Editor from "@monaco-editor/react";

// import "./App.css";


// function App() {
//     const [code, setCode] =
//         useState("");

//     const [output, setOutput] =
//         useState<string[]>([
//             "Welcome to <prototype 0> IDE"
//         ]);


//     async function compileAndRun() {
//         setOutput([
//             "Compiling and running..."
//         ]);

//         try {
//             const response =
//                 await fetch(
//                     "http://localhost:3001/compile",
//                     {
//                         method: "POST",

//                         headers: {
//                             "Content-Type":
//                                 "application/json"
//                         },

//                         body:
//                             JSON.stringify({
//                                 code: code
//                             })
//                     }
//                 );

//             const result =
//                 await response.json();


//             const lines =
//                 result.output
//                     .split("\n")
//                     .filter(
//                         (line: string) =>
//                             line.trim() !== ""
//                     );


//             setOutput(
//                 lines.length > 0
//                     ? lines
//                     : [
//                         result.success
//                             ? "Compilation finished successfully."
//                             : "Compilation failed."
//                     ]
//             );
//         }
//         catch (error) {
//             setOutput([
//                 "Error: Could not connect to compiler backend.",
//                 "Make sure server.js is running."
//             ]);
//         }
//     }


//     function saveFile() {
//         const blob =
//             new Blob(
//                 [code],
//                 {
//                     type:
//                         "text/plain"
//                 }
//             );

//         const url =
//             URL.createObjectURL(
//                 blob
//             );

//         const link =
//             document.createElement(
//                 "a"
//             );

//         link.href =
//             url;

//         link.download =
//             "source_code.p0";

//         link.click();

//         URL.revokeObjectURL(
//             url
//         );

//         setOutput([
//             "File saved as source_code.p0"
//         ]);
//     }


//     return (
//         <div className="ide">

//             <header className="ide-header">

//                 <h1>
//                     &lt;prototype 0&gt; IDE
//                 </h1>

//                 <div className="header-actions">

//                     <button
//                         onClick={saveFile}
//                     >
//                         Save
//                     </button>

//                     <button
//                         className="compile-button"
//                         onClick={compileAndRun}
//                     >
//                         Compile & Run
//                     </button>

//                 </div>

//             </header>


//             <div className="file-bar">
//                 source_code.p0
//             </div>


//             <main className="editor-container">

//                 <Editor
//                     height="100%"
//                     defaultLanguage="plaintext"
//                     value={code}
//                     onChange={
//                         (value) =>
//                             setCode(
//                                 value || ""
//                             )
//                     }
//                     theme="vs-dark"
//                     options={{
//                         fontSize: 16,

//                         fontFamily:
//                             "'Courier New', monospace",

//                         lineNumbers: "on",

//                         minimap: {
//                             enabled: false
//                         },

//                         scrollBeyondLastLine: false,

//                         automaticLayout: true,

//                         cursorBlinking: "blink",

//                         cursorStyle: "line",

//                         padding: {
//                             top: 10
//                         }
//                     }}
//                 />

//             </main>


//             <section className="output-panel">

//                 <div className="output-title">
//                     Messages / Output
//                 </div>

//                 <div className="output-content">

//                     {output.map(
//                         (
//                             message,
//                             index
//                         ) => (
//                             <div
//                                 key={index}
//                                 className="output-line"
//                             >
//                                 {message}
//                             </div>
//                         )
//                     )}

//                 </div>

//             </section>

//         </div>
//     );
// }


// export default App;

import { useState } from "react";
import Editor from "@monaco-editor/react";

import "./App.css";


function App() {
    const [code, setCode] =
        useState(
            `>>>
            p: "hi! welcome to prototype-0 IDE! pls refer to Syntax button to learn the syntax of prototype-0.\\n"
            p: "delete this sample code and start ur own. code away!"
            <<<`
        );

    const [output, setOutput] =
        useState<string[]>([
            "Welcome to <prototype 0> IDE"
        ]);


    async function compileAndRun() {
        setOutput([
            "Compiling and running..."
        ]);

        try {
            const response =
                await fetch(
                    "/compile",
                    {
                        method: "POST",

                        headers: {
                            "Content-Type":
                                "application/json"
                        },

                        body:
                            JSON.stringify({
                                code: code
                            })
                    }
                );

            const result =
                await response.json();


            const lines =
                result.output
                    .split("\n")
                    .filter(
                        (line: string) =>
                            line.trim() !== ""
                    );


            setOutput(
                lines.length > 0
                    ? lines
                    : [
                        result.success
                            ? "Compilation finished successfully."
                            : "Compilation failed."
                    ]
            );
        }
        // catch (error) {
        //     setOutput([
        //         "Error: Could not connect to compiler backend.",
        //         "Make sure server.js is running."
        //     ]);
        // }
        catch (error) {
            console.error(
                "Compile request failed:",
                error
            );

            setOutput([
                "Error: Could not reach /compile.",
                "Check the Render deployment logs."
            ]);
        }
    }


    function saveFile() {
        const blob =
            new Blob(
                [code],
                {
                    type:
                        "text/plain"
                }
            );

        const url =
            URL.createObjectURL(
                blob
            );

        const link =
            document.createElement(
                "a"
            );

        link.href =
            url;

        link.download =
            "source_code.p0";

        link.click();

        URL.revokeObjectURL(
            url
        );

        setOutput([
            "File saved as source_code.p0"
        ]);
    }


    return (
        <div className="ide">

            <header className="ide-header">

                <h1>
                    &lt;prototype 0&gt; IDE
                </h1>

                <div className="header-actions">

                    <button
                        onClick={saveFile}
                    >
                        Save
                    </button>

                    <button
                        className="compile-button"
                        onClick={compileAndRun}
                    >
                        Compile & Run
                    </button>

                    <button
                        className="syntax-button"
                        onClick={() => {
                            setOutput([
                                "Prototype-0 Syntax",
                                "",
                                "Use >>> to begin a program.",
                                'p: "text" prints text.',
                                "",
                                "Example:",
                                ">>>",
                                'p: "Hello, World!\\n"',
                                "<<<"
                            ]);
                        }}
                    >
                        Syntax
                    </button>

                </div>

            </header>


            <div className="file-bar">
                source_code.p0
            </div>


            <main className="editor-container">

                <Editor
                    // height="100%"
                    // defaultLanguage="plaintext"
                    // value={code}
                    // onChange={
                    //     (value) =>
                    //         setCode(
                    //             value || ""
                    //         )
                    // }
                    // theme="vs-dark"
                    // options={{
                    //     fontSize: 16,

                    //     fontFamily:
                    //         "'Courier New', monospace",

                    //     lineNumbers: "on",

                    //     minimap: {
                    //         enabled: false
                    //     },

                    //     scrollBeyondLastLine: false,

                    //     automaticLayout: true,

                    //     cursorBlinking: "blink",

                    //     cursorStyle: "line",

                    //     padding: {
                    //         top: 10
                    //     }
                    // }}
                    width="100%"
                    height="100%"
                    defaultLanguage="plaintext"
                    value={code}
                    onChange={
                        (value) =>
                            setCode(
                                value || ""
                            )
                    }
                    theme="vs-dark"
                    options={{
                        fontSize: 16,

                        // fontFamily:
                        //     "'Courier New', monospace",
                        fontFamily:
                            "'TurboDOS', 'Courier New', monospace",

                        lineNumbers: "on",

                        minimap: {
                            enabled: false
                        },

                        scrollBeyondLastLine: false,

                        automaticLayout: true,

                        cursorBlinking: "blink",

                        cursorStyle: "line",

                        padding: {
                            top: 10
                        }
                    }}
                />

            </main>


            <section className="output-panel">

                <div className="output-title">
                    Messages / Output
                </div>

                <div className="output-content">

                    {output.map(
                        (
                            message,
                            index
                        ) => (
                            <div
                                key={index}
                                className="output-line"
                            >
                                {message}
                            </div>
                        )
                    )}

                </div>

            </section>

        </div>
    );
}


export default App;