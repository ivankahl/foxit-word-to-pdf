const { exec } = require('child_process');
const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');
const { randomUUID } = require('crypto');

// Create a custom upload file storage for multer that places
// each file in a folder with a random UUID to avoid file name
// clashes.
const upload = multer({
  storage: multer.diskStorage({
    destination: (req, file, callback) => {
      // Generate new folder and ensure it exists.
      const folder = path.join(__dirname, 'files', randomUUID());
      fs.mkdirSync(folder, { recursive: true });

      callback(null, folder)
    },
    filename: (req, file, callback) => {
      callback(null, file.originalname);
    }
  })
});

const app = express();

app.get('/', (req, res) => {
  res.send("Hello, world!");
});

// Create post endpoint that accepts a file in a Form Data request.
// The file should be in a form field called "docxFile"
app.post('/', upload.single('docxFile'), (req, res) => {
  // Get DOCX file path
  const docxPath = req.file.path;
  // Create file path for PDF file
  const pdfPath = path.join(req.file.destination, path.parse(req.file.filename).name + '.pdf')
  
  // Event handler that will delete the temporary folder in `files` once the file
  // has been downloaded to the browser.
  res.on('finish', () => {
    fs.rmSync(req.file.destination, { recursive: true });
  })
  
  // Execute the C++ application, passing in the DOCX filename as the first parameter and the
  // PDF filename as the second.
  exec(`/app/sdk/convert "${docxPath}" "${pdfPath}"`, { timeout: 30000 }, (error, stdout, stderr) => {
    // Process any errors and return an error response to the user.
    if (error) {
      res.sendStatus(500).send("An unexpected error occurred. Please try again.");
      return;
    }

    // If there were no errors, send the file back in the response.
    res.sendFile(pdfPath);
  })
});

app.listen(process.env.PORT ?? 3000);
console.log("Server started on http://localhost:" + (process.env.PORT ?? 3000));