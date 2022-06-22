import logo from './logo.svg';
import { useState,useEffect } from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import './App.css';
import {Row,Col,Container,Navbar,Card, Button} from "react-bootstrap"
import axios from "axios"
import {BrowserRouter as Router,Routes,Route} from 'react-router-dom';
import ElectionPage from './Components/ElectionPage';
import LoginPage from './Components/LoginPage';
import Dashboard from './Components/dashboard';



function App() {

  return (
    <div className="App">
      {/* <ElectionPage/> */}
      <Router>
        <Routes>
          <Route path='/' element={<ElectionPage></ElectionPage>}/>
          <Route path='/login' element={<LoginPage/>}/>
          <Route path='/dashboard' element={<Dashboard/>}/>
        </Routes>
      </Router>

     
    </div>
  );
}

export default App;
